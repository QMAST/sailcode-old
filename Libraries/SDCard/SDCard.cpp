/*
SDCard.c

*/

#include "SDCard.h"

SDCard::SDCard(int pin)
{
	_list = NULL;

	_pin = pin;
	pinMode(_pin, OUTPUT);

	_logfile = (char*) malloc(sizeof(char)*14);

	if(DEBUG) 
		Serial.println("Initializing SD Card...");

	if(!SD.begin(_pin))
	{
		Serial.println("Initialization Failed");
		delay(5000);
		return;
	}

	//Create a new file, with the proper filename
	strcpy(_logfile, "MASTLOG00.txt");

	for(int i=0; i<100; i++)
	{
		logfile[7] = '0' + i/10;
		logfile[8] = '0' + i%10;
		if(!SD.exists(_logfile))
			break;
	}

	delay(2000);

	File testFile = SD.open(_logfile, FILE_WRITE);
	if(!testFile)
	{
		Serial.println("Couldn't Create File");
		delay(5000);
		return;
	}
	testFile.close();


	delay(5000);
}

char* SDCard::getFilename()
{
	//Returns a copy of the filename as a C string
	char* filename = (char*) malloc(sizeof(char)*14);
	strcpy(filename, _logfile);
	return filename;
}


/*
Adds a DataSource to the list of sources.
*/
void SDCard::addDataSource(char* label, void* data, DataType type)
{
	DataSource* link = (DataSource*) malloc(sizeof(DataSource));
	link->label = label;
	link->data = data;
	link->type = type;
	link->head = _list;
	_list = link;
}

/*
Writes all the dataSources to the file, returning a 0 if successful.
Error Codes:
	0 - File write successful
	1 - File failed to open

Need to test to see if floats can be written to the file without issue. 
If not, will need to write a method to do this. 
*/
int SDCard::writeLine()
{

	DataSource* link = _list;
	int* idata;
	double* ddata;
	char* cdata;
	float* fdata;

	//Open the file
	File f = SD.open(_logfile, FILE_WRITE);
	if(!f)//File failed to open
		return 1;


	while(link!=NULL)
	{
		f.write("###");
		f.flush();

		f.write(link->label);
		f.flush();
		switch(link->type) {
			case DataType.INT:
				idata = (int *) link->data;
				f.print(*idata, DEC);
				break;
			case DataType.DOUBLE:
				ddata = (double *) link->data;
				f.print(*ddata, DEC);
				break;
			case DataType.CHAR:
				cdata = (char *) link->data;
				f.write(cdata);
				break;
			case DataType.FLOAT:
				fdata = (float *) link->data;
				f.print(*fdata);
				break;
		}
		f.flush();
		f.write(",");
		f.flush();
		link=link->head;//Travel to the next link
	}
	//Close the file
	f.write("***\n");
	f.close();
}
