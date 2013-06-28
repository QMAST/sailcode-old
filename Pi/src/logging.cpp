#include "logging.h"

std::string Logging::errPath = "error00.log";
std::string Logging::dataPath = "data00.log";
std::list<DataSource> Logging::sources = std::list<DataSource>();

void Logging::init() {
	//Generate the paths for the logfiles.
	char dPath [] = "data00.log";
	char ePath [] = "error00.log";

	for(int i=0; i<100;i++)
	{
		dPath[4] = '0' + i/10;
		dPath[5] = '0' + i%10;
		struct stat buffer;
		if(stat(dPath, &buffer)!=0) {
			break;
		}
	}

	for(int i=0; i<100;i++)
	{
		ePath[5] = '0' + i/10;
		ePath[6] = '0' + i%10;
		struct stat buffer;
		if(stat(ePath, &buffer)!=0) {
			break;
		}
	}

	Logging::errPath = std::string(ePath);
	Logging::dataPath = std::string(dPath);

	Logging::sources = std::list<DataSource>();
	return;
}

void Logging::clean() {
	//Loop through the entire list of data sources
	std::list<DataSource>::iterator it;
	std::list<DataSource>::iterator end;
	for(it=Logging::sources.begin(), end=Logging::sources.end(); it != end; it++) 
	{ 
		switch(it->type) {
			case INT:
				delete ((int*) it->data);
			break;
			case DOUBLE:
				delete ((double*) it->data);
			break;
			case FLOAT:
				delete ((float*) it->data);
			break;
			case CHAR:
				delete ((char*) it->data);
			break;
			case STRING:
				delete ((std::string *)it->data);
			break;
		}
	}
}

int Logging::addDataSource(DataSource* src) {
	//check to see if null
	if(src==NULL || src->label.empty() || src->data==NULL) {
		Logging::error(__func__,"Null data source passed");
		return -1;
	}

	Logging::sources.push_back(*src);
	return 0;
}

int Logging::addDataSource(DataType type, const std::string &label, void* data) {
	DataSource* src = new DataSource;
	src->type = type;
	src->label = label;
	src->data = data;
	return addDataSource(src);
}

int Logging::log() {
	//Open file, if possible.
	if(Logging::dataPath.empty()) {
		Logging::error(__func__, "File path not initialized properly");
		return -1;
	}

	std::fstream fs();
	fs.open(Logging::dataPath.c_str(), std::fstream::out | std::fstream::app);
	if(!fs.is_open()) {
		Logging::error(__func__, "File failed to open.");
		return -1;
	}

	//Loop through the entire list of data sources
	std::list<DataSource>::iterator it;
	std::list<DataSource>::iterator end;
	fs<<Logging::getTimeStamp()<<":";
	for(it=Logging::sources.begin(), end=Logging::sources.end(); it != end; it++) 
	{ 
		if(it!=Logging::sources.begin())
		{
			fs<<",";
		}
		fs<< it->label <<" - ";

		switch(it->type) {
			case INT:
				fs<< *((int*) it->data);
			break;
			case DOUBLE:
				fs<< *((double*) it->data);
			break;
			case FLOAT:
				fs<< *((float*) it->data);
			break;
			case CHAR:
				fs<< *((char*) it->data);
			break;
			case STRING:
				fs<< *((std::string *)it->data);
			break;
		}

	}
	fs<<"###"<<std::endl;
	fs.close();
	return 0;
}

void Logging::error(const char* src, const std::string &msg) {
	//Print out the message to the error file
	if(Logging::errPath.empty()) {
		return;
	}

	std::fstream fs;
	fs.open(Logging::errPath.c_str(), std::fstream::out | std::fstream::app);
	if(!fs.is_open()) {
		return;
	}

	fs<<Logging::getTimeStamp()<<":"<<src<<"-"<<msg<<std::endl;

	fs.close();
	return;
}

std::string Logging::getTimeStamp() {
	time_t rawtime;
	struct tm * ptm;
	std::string timeStamp = "";
	time (&rawtime);
	ptm = gmtime(&rawtime);

	timeStamp +=std::to_string(ptm->tm_mday) + "/"
		+ std::to_string(ptm->tm_mon) + "/" + std::to_string(ptm->tm_year+1900)
		+ " " + std::to_string(ptm->tm_hour) + ":" + std::to_string(ptm->tm_min)
		+ ":" + std::to_string(ptm->tm_sec);
	return timeStamp;
}
