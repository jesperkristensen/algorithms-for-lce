#include "algDirectComp.h"
#include <stdio.h>

AlgorithmDirectComp::AlgorithmDirectComp() {
    this->s = NULL;
}

AlgorithmDirectComp::~AlgorithmDirectComp() {
}

bool AlgorithmDirectComp::preproc(TestString* s) {
    this->s = s;
    return true;
}

uint32 AlgorithmDirectComp::query(uint32 i, uint32 j) {
    TestString* d = this->s;
    uint32 t = 0;
    if (i == j)
        return d->n - i;
    while (d->s[i + t] == d->s[j + t]) {
        t++;
    }
    return t;
}

void AlgorithmDirectComp::cleanup() {
    this->s = NULL;
}

void AlgorithmDirectComp::getName(char* name, uint32 size) {
    snprintf(name, size, "DirectComp");
}

uint64 AlgorithmDirectComp::spaceUsage(uint32 n) {
    return sizeof(TestString*);
}

// Their implementations
/*


// x, y from 1 to length of string
inline int simple_lcp_2_suffixes(const char * const str, const unsigned int length, register int x, register int y){
    register int lcp = 0;
    while( (x-1 < length) && (y-1 < length) && (str[x-1] == str[y-1]) ){
        ++lcp;
        ++x;
        ++y;
    }
    return lcp;
}

// this version is for zero terminated text strings (C strings)
inline int simple_lcp_2_suffixes(const char * const str, const unsigned int x, const unsigned int y){
    register int lcp = 0;
    //const unsigned int *const int_str = (unsigned int*)str;
    const char *p = &(str[x-1]);
    const char *q = &(str[y-1]);
    while( *p++ == *q++ ) ++lcp;

    return lcp;
}


*/
