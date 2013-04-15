#ifndef kstrings
#define kstrings

#include <string.h>
#include <stdlib.h>

class kstring {
    public:
        char* str;
        int len;

        kstring( int length );
        ~kstring();
};
#endif
