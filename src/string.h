#ifndef _TESTSTRING_H_
#define _TESTSTRING_H_

#include "types.h"

enum string_type {RANDOM2_STRING, RANDOM4_STRING, RANDOM10_STRING, RANDOM255_STRING, ALL_A_STRING, RANDOM10_REPEAT10_STRING, REPEAT_POW_STRING};

class TestString {
public:
    /**
     * Create a new string
     *
     * Immediately call checkStr to check if everything went OK.
     *
     * @param n The length of the string to make (terminating \0 not included).
     * @param type The pattern used to create the string.
     */
    TestString(uint32, enum string_type);

    /**
     * Create a new string from a file
     *
     * Immediately call checkStr to check if everything went OK.
     *
     * @param fileName The path of the file to load.
     */
    TestString(const char* fileName);

    /**
     * Free all memory related to the string
     */
    ~TestString();

    /**
     * The string, a buffer of size n+1, where s[0..n-1] is the string of
     * characters >0, and s[n]=0.
     */
    uint8* s;

    /**
     * Length of the string, not counting the last 0 byte.
     */
    uint32 n;

    /**
     * A name for the string indictaing how it was built.
     */
    char name[20];

    // sa, sainv and lcp are lazily initialized 
    uint32* sa;
    uint32* sainv;
    uint32* lcp;

private:
    void buildSa();
};

/**
 * Returns true if s is a successfully initialized string.
 * Returns false and cleans up s if s was not successfully initialized.
 */
bool checkStr(TestString* s);

const char* nameStr(enum string_type type);

#endif
