#include "algRmqN.h"
#include <stdio.h>

AlgorithmRmqN::AlgorithmRmqN() {
    this->s = NULL;
}

AlgorithmRmqN::~AlgorithmRmqN() {
}

bool AlgorithmRmqN::preproc(TestString* s) {
    this->s = s;
    return true;
}

uint32 AlgorithmRmqN::query(uint32 i, uint32 j) {
    TestString* s = this->s;
    uint32 min, x;

    if (i == j)
        return s->n - i;

    i = s->sainv[i];
    j = s->sainv[j];

    if (i > j) {
        min = i;
        i = j;
        j = min;
    }

    min = s->lcp[j];
    for (x = i + 1; x < j; x++) {
        if (s->lcp[x] < min) {
            min = s->lcp[x];
        }
    }
    return min;
}

void AlgorithmRmqN::cleanup() {
    this->s = NULL;
}

void AlgorithmRmqN::getName(char* name, uint32 size) {
    snprintf(name, size, "RMQ<1;n>");
}

uint64 AlgorithmRmqN::spaceUsage(uint32 n) {
    return 2*n*sizeof(uint32); // from sainv and lcp
}
