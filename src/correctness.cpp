#include "correctness.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

#include "string.h"

void correctness(Algorithm** algs, enum string_type type) {
    uint32 x;
    uint32 alg;

    TestString* s = new (std::nothrow) TestString(100, type);
    if (!checkStr(s))
        return;
    for (alg = 0; algs[alg]; alg++) {
        bool success = algs[alg]->preproc(s);
        if (!success) {
            printf("CORRECTNESS ERROR alg=%i, OOM\n", alg);
            for (x = 0; x < alg; x++) {
                algs[x]->cleanup();
            }
            return;
        }
    }

    for (x = 0; x < 10000; x++) {
        uint32 i = rand() % s->n;
        uint32 j = rand() % s->n;
        uint32 lce0 = algs[0]->query(i, j);
        for (alg = 1; algs[alg]; alg++) {
            uint32 lce1 = algs[alg]->query(i, j);
            if (lce0 != lce1) {
                printf("CORRECTNESS ERROR alg=%i, i=%i, j=%i, lce0=%i, lce1=%i\n", alg, i, j, lce0, lce1);
                return;
            }
        }
    }
    for (alg = 0; algs[alg]; alg++) {
        algs[alg]->cleanup();
    }
    delete s;
    printf("correct\n");
}
