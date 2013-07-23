#include "aisMessage.h"

AISMessage::AISMessage(const std::string &rawString) {
	//Takes a raw string from the NMEA parsed data and loads it into the bitstream.
	//Doesn't do any parsing with it.
	int len  = rawString.length();
	int offset=0;
	this->streamSize = (len*3)/4 + 1;
	unsigned char pkg;
	const char tmpPkg;

	int mod;
	this->bitstream = new char[streamSize];
	
	for(int i=0; i<(this->streamSize); i++) {
		this->bitstream[i] = 0;
	}


	for(int i=0; i<len;i++) {
		//The number of bits written in index offset/8 is given by 8 - offset%8.
		//The rest are written in offset/8 +1;
		tmpPkg = rawString[i];
		pkg = (unsigned) tmpPkg - 48; //Need to copy value, to avoid pass-by reference issue;
		if(pkg > 40) pkg -= 8;
		
		pkg = pkg << 2;
		mod = offset%8;

		this->bitstream[offset/8] |= pkg >> mod;
		this->bitstream[offset/8 + 1] |= pkg << 8-mod;
		offset += 6;
	}
}

unsigned char* AISMessage::getBits(int start, int length) {
	/*
		Returns an array of the bits requested. padded with 0s.
		start is the zero-indexed position in the message.
	*/
	int num = ((length-1)/8) + 1;
	unsigned char* data = new unsigned char[num];
	int mod = start%8;
	unsigned char mask = 0xFF << mod;
	int j;

	for(int i = 0, j=start/8; i<num; j++, i++) {
		//Fills up the entire byte - it will be masked off later
		data[i] = bitstream[j] << mod;

		if((j+1) < this->streamSize) {
			data[i] |= ((bitstream[j+1] >> 8-mod) & ~mask);
		}
	}

	//now just mask off the end, so its zeros beyond the length.
	mask = 0xFF << (length%8);
	data[num-1] &= mask;
	return data;
}

int AISMessage::getInt(int start, int length) {
	//Gets a signed integer from the bitstream.
	int maxInd = (length-1)/8;
	int num = 0;
	unsigned char* raw = this->getBits(start, length);
	//first, extract the sign bit - this is the most significant bit in the bitstream.
	//This will need to be written to the most significant bit of the int.
	//The rest of the bits are just written to the least significant bits
	//of the int num. Write from least sig to most sig.
	//There is going to be an offset in each byte, which makes sense. 
	int offset = 8 - (length%8);
	int shift = 0;
	for(int i = maxInd; i>=0; i--) {
		num |= (raw[i] >> offset) <<shift;
		shift+=8;
	}
	//Now, mask off the raw sign bit in num, and set the sign bit in the int.
	int mask = 1 <<(length-1);
	if((num & mask)>0) {
		num &= (~mask);
		num |= 0x80000000;//Set the sign bit.
	}

	delete[] raw; 
	return num;
}

unsigned int AISMessage::getUInt(int start, int length) {
	//Gets an unsigned integer from the bitstream.
	int maxInd = (length-1)/8;
	unsigned int num = 0;
	unsigned char* raw = this->getBits(start, length);

	int offset = 8 - (length%8);
	int shift = 0;
	for(int i = maxInd; i>=0; i--) {
		num |= (raw[i] >> offset) <<shift;
		shift+=8;
	}

	delete[] raw;
	return num;
}

std::string AISMessage::getString(int start, int length) {
	if(length%6 !=0) {
		return NULL;
	}
	//Get a message from the bitstream, interpretting using 6-bit ASCII
	unsigned char* raw = this->getBits(start, length);
	//Need to parse 6 bit "nibbles" at a time, into chars.
	int num = length/6;
	char* str = new char[num];

	int bytePos =0;//Position within an individual byte.
	unsigned char mask=0;
	for(int i=0, int j=0; i<num; i++) {
		str[i] = 0;
		mask = 0xFC >> bytePos; 
		str[i] |= (raw[j] & mask)<<bytepos;
		if(bytePos>2) {
			mask = 0xFF << (6 - bytePos);//Mask off the number of bits that are needed from the 2nd byte
			str[i] | = (raw[j+1] & mask) >> 8-bytePos;
		}
		str[i] = (str[i]>>2) & 0x3F;
		if(i<31) {
			str[i] += '@';
		} else {
			str[i] += ' ';
		}
	}

	delete[] raw;

	std::string returnVal(str);
	delete[] str;
	return returnVal;
}

