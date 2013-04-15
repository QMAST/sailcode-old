#include "kstrings.h"

kstring::kstring( int length ) {
    this->len = length;
    this->str = (char*) 
        malloc( sizeof(char) * ( length + 1 ) );
    this->str[length] = '\0';
}

kstring::~kstring() {
    free(this->str);
}
