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

int kstring::compare(kstring* alien_string) {
    int max = this->len > alien_string->len ? 
        alien_string->len : this->len;
    return strncmp(this->str, alien_string->str, max);
}
