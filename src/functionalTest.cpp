#include "functionalTest.h"
#include "string.h"
#include "testRandom.h"
#include <new>
#include <stdlib.h>

void functionalTest(Algorithm** algs) {
    uint32 paircount = 1000000;
    uint32 n = 1000;
    uint32 j;

    uint32* pairs = new (std::nothrow) uint32[paircount*2];
    if (!pairs) {
        return;
    }
    for (uint32 i = 0; i < paircount*2; i += 2) {
        pairs[i] = rand() % n;
        pairs[i + 1] = rand() % n;
    }

    TestString* s = new (std::nothrow) TestString(n, ALL_A_STRING);
    if (!checkStr(s)) {
        delete[] pairs;
        return;
    }
    for (j = 0; algs[j]; j++)
        testRandom(s, pairs, paircount, algs[j], true, 1);
    delete s;

    s = new (std::nothrow) TestString(n, RANDOM10_STRING);
    if (!checkStr(s))
        return;
    for (j = 0; algs[j]; j++)
        testRandom(s, pairs, paircount, algs[j], true, 1);
    delete s;
    delete[] pairs;
}
