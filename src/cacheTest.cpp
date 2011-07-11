#include "cacheTest.h"
#include "algorithm.h"
#include "algRmq1.h"
#include "testRandom.h"
#include <iostream>
#include <stdlib.h>

void cacheTest(uint32 n, enum string_type type) {
    std::cout << "Cachegrind test for string " << nameStr(type) << " length " << n << "\n";
    Algorithm* rmq1 = new AlgorithmRmq1;

    uint32 paircount = 1000000;
    uint32* pairs = new (std::nothrow) uint32[paircount*2];
    if (!pairs) {
        delete rmq1;
        std::cout << "Cannot allocate pairs\n";
        return;
    }

    for (uint32 i = 0; i < paircount*2; i += 2) {
        pairs[i] = rand() % n;
        pairs[i + 1] = rand() % n;
    }

    TestString* s = new (std::nothrow) TestString(n, type);
    if (!checkStr(s)) {
        delete rmq1;
        delete pairs;
        std::cout << "Cannot allocate string\n";
        return;
    }
    
    double time = testRandom(s, pairs, paircount, rmq1, false, 10000);
    std::cout << "Time was " << time << ".\n";
}
