#include "algDirectCompLookup.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

AlgorithmDirectCompLookup::AlgorithmDirectCompLookup(NamedFunc* f) {
    s = NULL;
    table = NULL;
    n = 0;
    S_CLEAR(nn)
    S_CLEAR_MOD(t)
    this->f = f;
    fp = 0;
}

AlgorithmDirectCompLookup::AlgorithmDirectCompLookup(NamedFunc* f, uint32 fp) {
    s = NULL;
    table = NULL;
    n = 0;
    S_CLEAR(nn)
    S_CLEAR_MOD(t)
    this->f = f;
    this->fp = fp;
}

AlgorithmDirectCompLookup::~AlgorithmDirectCompLookup() {
}

bool AlgorithmDirectCompLookup::preproc(TestString* ts) {
    uint32 t = f->f(ts->n);
    if (fp)
        t = f->f(fp);
    uint32 i, j, k, cur;
    uint64 size;

    uint32 nn = ts->n;
    S_PREP(nn)
    S_PREP_MOD(t)
    size = (uint64)ts->n * (S_DIV((uint64) nn, t) + 1u);
    if (size > INT32_MAX/sizeof(uint32)) {
        S_CLEAR(nn);
        S_CLEAR_MOD(t)
        return false;
    }
    table = new (std::nothrow) uint32[size];
    if (!table) {
        S_CLEAR(nn)
        S_CLEAR_MOD(t)
        return false;
    }
    s = ts->s;
    n = ts->n;
    for (k = 1; k < n; k++) {
        cur = 0;
        for (i = n-k-1; (int32)i >= 0; i--) {
            j = i + k;
            if (s[i] == s[j])
                cur++;
            else
                cur = 0;
            if (!S_MOD(i, t)) {
                table[S_MUL(S_DIV(i, t), nn) + j] = cur;
            }
        }
    }
    return true;
}

uint32 AlgorithmDirectCompLookup::query(uint32 i, uint32 j) {
    uint32 v = j;
    if (i == j)
        return n - i;
    else if (i > j) {
        j = i;
        i = v;
    }
    v = 0;

    while (s[i + v] == s[j + v]) {
        if (!S_MOD(i + v, t)) {
            return v + table[S_MUL(S_DIV(i + v, t), nn) + (j + v)];
        }
        v++;
    }
    return v;
}

void AlgorithmDirectCompLookup::cleanup() {
    delete[] table;
    s = NULL;
    table = NULL;
    n = 0;
    S_CLEAR(nn)
    S_CLEAR_MOD(t)
}

void AlgorithmDirectCompLookup::getName(char* name, uint32 size) {
    snprintf(name, size, "DirectCompLookup<%s>", f->name);
}

uint64 AlgorithmDirectCompLookup::spaceUsage(uint32 n) {
    uint32 t = f->f(n);
    uint32 nn = n;
    S_DECL(nn)
    S_DECL(t)
    S_PREP(nn)
    S_PREP(t)
    return (uint64)n * (S_DIV((uint64) nn, t) + 1u) * sizeof(uint32)
        + sizeof(AlgorithmDirectCompLookup);
}
