#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <new>
#include <iostream>
#include <math.h>

#include "buildSa.cpp"
TestString::~TestString() {
    if (s)
        delete[] s;
    if (sa)
        delete[] sa;
    if (sa)
        delete[] sainv;
    if (lcp)
        delete[] lcp;
}

const char* nameStr(enum string_type type) {
    switch (type) {
    case RANDOM2_STRING:
        return "Random-2";
    case RANDOM4_STRING:
        return "Random-4";
    case RANDOM10_STRING:
        return "Random-10";
    case RANDOM255_STRING:
        return "Random-255";
    case ALL_A_STRING:
        return "All ´a´";
    case RANDOM10_REPEAT10_STRING:
        return "Random-10-Repeat-10";
    case REPEAT_POW_STRING:
        return "Repeat-pow";
    default:
        return "UNKNOWN";
    }
}

/**
 * Initializes a pre-allocated buffer s->s of size n+1 with a string of
 * length s->n with characters from the alphabet [1..mod], where each character
 * is chosen uniformly at random.
 */
void strRandom(TestString* s, uint8 mod, bool print) {
    uint32 i;
    if (print) std::cout << "String: ";
    for (i = 0; i < s->n; i++) {
        s->s[i] = rand() % mod + 1;
        if (print) std::cout << std::hex << s->s[i];
    }
    s->s[s->n] = 0;
    if (print) std::cout << ", n=" << s->n << "\n";
    snprintf(s->name, 20, "random n=%i c=%i", s->n, mod);
}

void strAllA(TestString* s) {
    uint32 i;
    for (i = 0; i < s->n; i++) s->s[i] = 'a';
    s->s[s->n] = 0;
    snprintf(s->name, 20, "all a n=%i", s->n);
}

void strRepeat(TestString* s, uint32 len) {
    uint32 i;
    for (i = 0; i < s->n; i++) s->s[i] = '1' + (i % len);
    s->s[s->n] = 0;
    snprintf(s->name, 20, "repeat %i n=%i", len, s->n);
}

TestString::TestString(uint32 n, enum string_type type) {
    this->n = n;
    this->s = new (std::nothrow) uint8[n+1];
    if (!this->s)
        return;
    switch (type) {
    case RANDOM2_STRING:
        strRandom(this, 2, false);
        break;
    case RANDOM4_STRING:
        strRandom(this, 4, false);
        break;
    case RANDOM10_STRING:
        strRandom(this, 10, false);
        break;
    case RANDOM255_STRING:
        strRandom(this, 255, false);
        break;
    case ALL_A_STRING:
        strAllA(this);
        break;
    case RANDOM10_REPEAT10_STRING:
        this->n = n/10;
        strRandom(this, 10, false);
        for (uint32 i = 0; i < n; i++)
            this->s[i] = this->s[i % this->n];
        this->s[n] = 0;
        this->n = n;
        break;
    case REPEAT_POW_STRING:
        uint32 p = (uint32) (0.73*pow(n, 0.42) + 0.5);
        strRepeat(this, p);
        break;
    }
    buildSa();
}

TestString::TestString(const char* fileName) {
    FILE* file = fopen(fileName, "rb");
    if (!file) {
        std::cout << "There is an error opening the file.\n";
        // if( errno == EOVERFLOW ) std::cout << "TRUE" << "\n";
        return;
    }

    off_t filesize = -1;
    off_t p = ftell(file); // get the current position
    if(!fseek(file, 0, SEEK_END)) { // go to the end
        filesize = ftell(file); // get current position = file size
        fseek(file, p, SEEK_SET); // set back old position
    }
    s = new (std::nothrow) uint8[filesize + 1];
    if (!s) {
        fclose(file);
        return;
    }
    n = fread(s, 1, static_cast<size_t>(filesize), file);
    s[n] = 0;
    //cout << "Errno: " << errno << endl;

    fclose(file);

    buildSa();
}

bool checkStr(TestString* s) {
    if (!s)
        return false;
    if (!s->lcp) {
        delete s;
        return false;
    }
    return true;
}
