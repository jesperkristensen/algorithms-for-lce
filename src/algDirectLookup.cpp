#include "algDirectLookup.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

AlgorithmDirectLookup::AlgorithmDirectLookup() {
    this->table = NULL;
    this->n = 0;
    this->sham = 0;
}

AlgorithmDirectLookup::~AlgorithmDirectLookup() {
}

// TODO kan det allokerede adresserum gøres mere kompakt?
bool AlgorithmDirectLookup::preproc(TestString* s) {
    uint32 i, j, k, cur;
    uint64 size;
    this->n = s->n;
    this->sham = 0;
    while (1u<<this->sham < s->n)
        this->sham++;
    size = (uint64)s->n*((uint64)1u<<this->sham);
    if (size > INT32_MAX/sizeof(uint32)) {
        this->n = 0;
        this->sham = 0;
        return false;
    }
    this->table = new (std::nothrow) uint32[size];
    if (!this->table) {
        this->n = 0;
        this->sham = 0;
        return false;
    }
    for (k = 1; k < s->n; k++) {
        cur = 0;
        for (i = s->n-k-1; (int32)i >= 0; i--) {
            j = i + k;
            if (s->s[i] == s->s[j])
                cur++;
            else
                cur = 0;
            this->table[(i<<this->sham) + j] = cur;
        }
    }
    return true;
}

uint32 AlgorithmDirectLookup::query(uint32 i, uint32 j) {
    if (i < j)
        return this->table[(i<<this->sham) + j];
    else if (i > j)
        return this->table[(j<<this->sham) + i];
    else
        return this->n - i;
}

void AlgorithmDirectLookup::cleanup() {
    delete[] this->table;
    this->table = NULL;
    this->n = 0;
    this->sham = 0;
}

void AlgorithmDirectLookup::getName(char* name, uint32 size) {
    snprintf(name, size, "DirectLookup");
}

uint64 AlgorithmDirectLookup::spaceUsage(uint32 n) {
    uint32 sham = 0;
    while (1u<<sham < n)
        sham++;
    return (uint64)n*((uint64)1u<<sham)*sizeof(uint32)
        + sizeof(AlgorithmDirectLookup);
}
