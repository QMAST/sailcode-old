#include "sensor.h"
#define DEBUG 0


char** Sensor::getVariables(int argc, char* argv[]) {
	/*
	This function returns a string of comma separated values
	containing all the variables in the varList which have id's 
	matching one of the argv strings. argc should match the number
	of elements in argv[]. Additionally, all the arguments should be
	valid sources in the varList.
	*/

	//Serial.println("Entering getVariables..");
	int totLen=0;
	char** variables = (char**) malloc(sizeof(char*)*argc);
	for(int i=0; i<argc; i++){
		variables[i]=NULL;//Initialize to NULL pointers.
	}

	DataSource* item = this->varList;
	if(item==NULL) {
		free(variables);
		return NULL;//No variables registered, can't return anything.
	}

	while(item != NULL) {
		//Serial.print("Looking for match for ");
		//Serial.println(item->id);
		for(int i=0; i<argc; i++) {
			//Serial.print(argv[i]);
			//Serial.print(" ");
			if(strcmp(argv[i],item->id)==0) {//Item is found
				//Convert item to c-string
				char* buf= (char*) calloc(255,sizeof(char));
				int len;
				switch(item->type) {
					case INT:
						len = sprintf(buf,"%d", *((int*) item->data))+1;
					break;
					case DOUBLE:
						//Sprintf for doubles/floats isn't implemented on Arduino.
						//Will have to use a workaround.
						dtostrf(*(double*)item->data, 1, 4, buf);
						len = strlen(buf) +1;
						Serial.print(" '");
						Serial.print(buf);
						Serial.print("' -");
						Serial.print(len);
					break;
					case CHAR:
						len = sprintf(buf,"%d", *((char*) item->data)) +1;
					break;
					case FLOAT:
						dtostrf(*(float*)item->data, 1, 4, buf);
						len = strlen(buf) +1;
					break;
					case STRING:
						len = strlen((char*) item->data) +1;
						strcpy(buf, (char*) item->data);
					break;
				}

				variables[i] = (char*) malloc(len*sizeof(char));
				strcpy(variables[i], buf);
				totLen+=len;
				free(buf);
				break;
			}
		}
		//Serial.print("\n");
		item = item->next;
		
	}

/*
	Serial.println("getVariables is returning: ");
	for(int i=0; i<argc ; i++){
		Serial.print(variables[i]);
		Serial.print(" ");
	}
	Serial.println("");*/
	return variables;
}

int Sensor::addVar(DataType type, const char* id, void* data) {
	DataSource* link = (DataSource*) malloc(sizeof(DataSource));
	int len = strlen(id);
	link->type = type;
	link->data = data;
	link->id = (char*) malloc(sizeof(char)*(len+1));
	strcpy(link->id, id);
	link->id[len]='\0';
	//Might as well just prepend, not worry about appending.
	link->next = this->varList;
	this->varList = link;
	return 0;
}
