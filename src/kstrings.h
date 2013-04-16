#ifndef kstrings
#define kstrings

#include <string.h>
#include <stdlib.h>

class kstring {
    public:
        static const int MAX_STRING_SIZE = 1024;
        char* str;
        int len;

        kstring( int length );
        kstring( char* );
        ~kstring();

        int compare(kstring* src_string);
        int compare(char* src_string);


};
#endif
