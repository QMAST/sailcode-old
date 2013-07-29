#include "aisManager.h"

AISManager::AISManager(const std::string &path) {
	//Initialize the AISManager object, opening the serial port.
	this->fildes=-1;
	int stat = this->openPort(path, B9600);//Need to check the baud rate on this.
	if(stat!=0) {
		Logging::error(__func__, "Unable to set up the AIS.");
	}
}

int AISManager::update() {
	/*
		This function will read data from the AIS and update the knowledge of surrounding ships.
		I am unsure of the best way to approach this - reading one line at a time seems risky,
		since we could miss important information. So we'll read a fixed number of sentences at once, say 5.
	*/
	int stat;
	std::string sentence;
	AISMessage* msg;
	for(int i=0;i<5;i++) {
		stat = this->readSentence(sentence);
		if(stat==0) {//Sentence was read successfully
			//Now I need to parse the sentence.
			msg = new AISMessage(sentence);

			//We want to parse the string. The string could be of many different types though,
			//so having a generic parser could be tough, if we need to return something.
			//So we will parse within the AIS manager class, to be able to return values as necessary.
			this->parse(msg);


			delete msg;
		}
	}

	return 0;
}

int AISManager::readSentence(std::string &payload) {
	bool finished = false;
	int stat;
	payload="";
	std::string line ="";
	int numFragments;
	int fragNumber;
	int messageId = -1;

	while(!finished) {
		int i=0;

		//Read line
		stat = this->readBlock(line);
		if(stat!=0){
			Logging::error(__func__, "Line not read successfully.");
			return -1;
		}
		//Checksum, verify validity of sentence
		if(line[0]!='$'&&line[0]!='!') {
			//Invalid NMEA sentence - something weird happened
			Logging::error(__func__, "Invalid NMEA string.");
			return -1;
		}
		if(!validChecksum(line)){
			//Invalid checksum - somethings been switched.
			Logging::error(__func__, "Invalid checksum");
			return -1;
		}

		//extract payload.
		//First, check the header, make sure it matches AIVDM
		if(line.find("AIVDM")!=1) {
			Logging::error(__func__, "Unrecognized NMEA Header");
			return -1;
		}

		//Find number of fragments in this sentence
		while(line[i]!=',') i++;
		i++;
		numFragments = atoi(&(line.c_str()[i]));
		//Get fragment number
		while(line[i]!=',') i++;
		i++;
		fragNumber = atoi(&(line.c_str()[i]));

		//Get the message ID, to make sure we're reading two parts of the same message
		while(line[i]!=',') i++;
		i++;
		int tempID = atoi(&(line.c_str()[i]));
		if(messageId!=-1 && tempID!=messageId){
			Logging::error(__func__, "Discontinuous message");
			return -1;
		}

		//Next field is the AIS channel, we don't really care about that.
		while(line[i]!=',') i++;
		i++;

		//Next field is the message.
		while(line[i]!=',') i++;
		i++;
		int pos = line.find('*');
		payload += line.substr(i, pos-i);
		if(fragNumber == numFragments) {
			finished=true;
		}
	}

	return 0;
}

bool AISManager::validChecksum(const std::string &line) {
	//Takes a full NMEA line and checks to see if the checksum is valid.

	//First, get the checksum bits from the line.
	int pos = line.find('*');
	unsigned char chk = (hexToDecimal(line[pos+1]) << 4)
							|| (hexToDecimal(line[pos+2]));//The checksum as read.
	unsigned char sum = 0;
	for(int i=1; i<pos;i++){
		sum ^= line[i];
	}

	return (sum==chk);
}

unsigned char AISManager::hexToDecimal(char hex) {
	return (hex>='A') ? (hex- 'A' + 10) : (hex - '0'); //converts a hex character into a decimal number.
}

bool AISManager::parse(AISMessage* msg){
	unsigned int type = msg->getUInt(0, 6);
	switch(type) {
		case 1:
		case 2:
		case 3:
			this->parseType1(msg);
		break;
		case 4:
			this->parseType4(msg);

		break;
		default:
			Logging::error(__func__, "Unsupported AIS message type: "+std::to_string(type));
		break;
	}

	return true;
}

void AISManager::parseType1(AISMessage* msg) {
	//Parses a message of type 1.
	//Message types 1, 2, and 3 are all the same, so this should parse any of those as well.

	//First six bits are message type, should already have been parsed.
	//Bits 6-7 are the repeat indicator. Doesn't affect us, we can't repeat.
	//Bits 8-37 are an MMSI. it is an unsigned integer, with 9 decimal digits.
	//This uniquely identifies a ships radio. This is our ship ID.
	unsigned int mmsi = msg->getUInt(8, 30);

	//Bits 38-41 are the navigation status. This is an enumerated type, from 0 to 15
	//One 0 to 8 are actually relevant.
	//unsigned int navStatus = msg->getUInt(38, 4);

	//Bits 42-49 are the rate of turn, a float, derived from an integer.
	//float rot = msg->getInt(42, 8) / 1000.0f;

	//Bits 50-59 are the speed over ground. This is really important. Pay lots of attention to this.
	float sog = msg->getInt(50, 10) / 10.0f;

	//Bit 60 is a position accuracy indicator. 1 indicated a fix with error of <10m. 0 indicates otherwise.
	//unsigned int positionAccuracy =  msg->getUInt(60, 1);

	//Bits 61-88 and 89-115 are longitude and latitude, respectively. They are divided by 60000 to convert to degrees.
	float lon = msg->getInt(61, 28) / 600000.0f;
	float lat = msg->getInt(89, 27) / 600000.0f;

	//Bits 116-127 are Course over ground, relative to true north.
	//Given in degrees to the nearest tenth
	float cog = msg->getInt(116, 12) / 10.0f;

	//Bits 128-136 are heading, from 0-359.
	//int hdg = msg->getUInt(128, 9);

	//Bits 137-142 are the time stamp. Probably will be unused
	//int second =  msg->getUInt(137, 6);//Second of UTC Timestamp

	//Bits 143-144 are the maneuver indicator. Unused right now.
	//The rest is reserved or not useful to us. 

	/*
		Now have to create a ship object which holds this data, and can be updated if available.
		So first, seach list of ships for this MMSI, and then if it doesn't exist, create it.
	*/

	Ship* boat = NULL;
	//First loop through all the existing boats, trying to find an mmsi match.
	for(std::list<Ship*>::iterator it = ships.begin(); it!=ships.end(); it++) {
		//it is of type Ship**.
		if((*it)->id==mmsi) {
			boat = (*it);
			continue;
		}

		//We can also clear out the list of old boats while looping through here.
		//If we haven't updated the boat in an hour, remove it.
		if(difftime(time(NULL), (*it)->lastUpdated) > 3600) {
			it = ships.erase(it);
			it--;
		}
	}

	if(boat==NULL) {
		boat = new Ship();
		ships.push_back(boat);
	}

	//Update boat information.
	boat->id = mmsi;
	boat->speedOverGround = sog;
	boat->courseOverGround = cog;
	boat->lon = lon;
	boat->lat = lat;
	boat->lastUpdated = time(NULL);
	
}

void AISManager::parseType4(AISMessage* msg) {
	//Type 4 is a base station report. Fixed location base stations report a position and time reference.

	//Bits 0-5 are the message type again. Should already be checked.

	//Bits 8-37 are MMSI.
	unsigned int mmsi = msg->getUInt(8, 30);
	//The next bunch of bits contain the present time, but this can just be ignored.

	float lon = msg->getInt(79, 28) / 600000.0f;
	float lat = msg->getInt(107, 27) /600000.0f;

	//We'll treat a base station like a boat, just not moving.
	Ship* boat = NULL;
	//First loop through all the existing boats, trying to find an mmsi match.
	for(std::list<Ship*>::iterator it = ships.begin(); it!=ships.end(); it++) {
		//it is of type Ship**.
		if((*it)->id==mmsi) {
			boat = (*it);
			continue;
		}

		//We can also clear out the list of old boats while looping through here.
		//If we haven't updated the boat in an hour, remove it.
		if(difftime(time(NULL), (*it)->lastUpdated) > 3600) {
			it = ships.erase(it);
			it--;
		}
	}

	if(boat==NULL) {
		boat = new Ship();
		ships.push_back(boat);
	}

	//Update boat information.
	boat->id = mmsi;
	boat->speedOverGround = 0;
	boat->courseOverGround = 0;
	boat->lon = lon;
	boat->lat = lat;
	boat->lastUpdated = time(NULL);
}