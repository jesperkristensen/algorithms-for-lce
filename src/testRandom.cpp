#include "testRandom.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

/**
 * Tests a given agorithm on a given string using random query pairs.
 */
double testRandom(TestString* s, uint32* pairs, uint32 paircount, Algorithm* a, bool print, double preproc_time_limit) {
    uint32 x;
    double start;
    double end;
    char algName[ALGORITHM_NAME_SIZE];
    a->getName(algName, ALGORITHM_NAME_SIZE);
    if (a->spaceUsage(s->n) > 1e9) {
        if (print) printf("\ntestRandom,%s,too much memory,%s\n", algName, s->name);
        return -1;
    }
    start = gettime();
    bool success = a->preproc(s);
    end = gettime();
    if (!success) {
        if (print) printf("\ntestRandom,%s,out of memory,%s\n", algName, s->name);
        return -1;
    }
    if (end - start > preproc_time_limit) {
        a->cleanup();
        if (print) printf("\ntestRandom,%s,preprocessing timed out,%s\n", algName, s->name);
        return -1;
    }
    start = gettime();
    for (x = 0; x < paircount*2; x += 2) {
        uint32 i = pairs[x];
        uint32 j = pairs[x + 1];
        uint32 lce = a->query(i, j);
        //printf("i=%i, j=%i, lce=%i\n", i, j, lce);
    }
    end = gettime();
    if (print) printf("\ntestRandom,%s,%e,%s\n", algName, (end - start) / (double) paircount, s->name);
    a->cleanup();
    return (end - start) / (double) paircount;
}
