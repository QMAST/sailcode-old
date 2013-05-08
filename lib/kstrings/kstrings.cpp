#include "kstrings.h"

kstring::kstring( int length ) {
    this->len = length;
    this->str = (char*) malloc( sizeof(char) * ( length + 1 ) );
    this->str[length] = '\0';
}

kstring::~kstring() {
    free(this->str);
}

kstring::kstring( char* src_string ) {
    int new_len = strnlen(src_string, this->MAX_STRING_SIZE);

    this->len = new_len;
    this->str = (char*) malloc( sizeof(char) * ( new_len + 1 ) );
    this->str[new_len] = '\0';

    strncpy(this->str, src_string, new_len);
}

int kstring::compare(kstring* src_string) {
    int max = this->len > src_string->len ? 
        src_string->len : this->len;
    return strncmp(this->str, src_string->str, max);
}

int kstring::compare(char* src_string) {
    int src_string_len = strnlen(src_string, this->MAX_STRING_SIZE);
    int max = this->len > src_string_len ? 
        this->len : src_string_len;

    return strncmp(this->str, src_string, max);
}

