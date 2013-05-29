#include "sensor.h"

char** Sensor::getVariables(int argc, char* argv[]) {
	/*
	This function returns a string of comma separated values
	containing all the variables in the varList which have id's 
	matching one of the argv strings. argc should match the number
	of elements in argv[]. Additionally, all the arguments should be
	valid sources in the varList.
	*/
	int totLen=0;
	char** variables = (char**) malloc(sizeof(char*)*argc);
	for(int i=0; i<argc; i++){
		variables[i]=NULL;//Initialize to NULL pointers.
	}

	DataSource* item = varList;
	if(item==NULL) {
		return NULL;//No variables registered, can't return anything.
	}

	while(item != NULL) {
		for(int i=0; i<argc; i++) {
			if(strcmp(argv[i],item->id)==0) {//Item is found
				
				//Convert item to c-string
				char* buf= (char*) calloc(255,sizeof(char));
				int len;
				switch(item->type) {
					case INT:
						len = sprintf(buf,"%d", *((int*) item->data));
					break;
					case DOUBLE:
						len = sprintf(buf,"%.4f", *((double*) item->data));
					break;
					case CHAR:
						len = sprintf(buf,"%d", *((char*) item->data));
					break;
					case FLOAT:
						len = sprintf(buf,"%f", *((float*) item->data));
					break;
					case STRING:
						len = strlen((char*) item->data);
						strcpy(buf, (char*) item->data);
					break;
				}

				variables[i] = (char*) malloc(len*sizeof(char));
				strcpy(variables[i], buf);
				totLen+=len;
			}
		}
		item = item->next;
	}

	return variables;
}

int Sensor::addVar(DataType type, const char* id, void* data) {
	DataSource* link = (DataSource*) malloc(sizeof(DataSource));
	int len = strlen(id);
	link->type = type;
	link->data = data;
	link->label = (char*) malloc(sizeof(char)*len);
	strcpy(link->label, id);

	//Might as well just prepend, not worry about appending.
	link->next = this->varList;
	this->varList = link;
}
