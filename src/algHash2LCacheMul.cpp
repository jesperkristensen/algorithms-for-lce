#include "algHash2LCacheMul.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint2AQCacheHorizMult::Fingerprint2AQCacheHorizMult(NamedFunc* f) {
    s = NULL;
    n = 0;
    H = NULL;
    t = 0;
    this->f = f;
    ndt = 0;
}

#define HH(i) ((i)%t)*ndt + (i)/t

Fingerprint2AQCacheHorizMult::~Fingerprint2AQCacheHorizMult() {
}

bool Fingerprint2AQCacheHorizMult::preproc(TestString* ts) {
    s = ts->s;
    n = ts->n;

    t = f->f(n);
    if (t < 1)
        t = 1;

    // ndt = ceil((n+1)/t)
    ndt = (n+1+t)/t;

    uint32 max = (t - 1)*ndt + n/t;

    H = new (std::nothrow) uint32[max+1];
    if (!H) {
        s = NULL;
        n = 0;
        t = 0;
        ndt = 0;
        return false;
    }

    uint32 h;
    // loop through each suffix s->sa[i] in sorted order.
    for (uint32 i = 0; i < n; i++) {
        // if suffix s->sa[i] does not have a prefix of length t in common with its predecessor, then update the current hash
        if (ts->lcp[i] < t)
            h = i;
        H[HH(ts->sa[i])] = h;
    }
    H[HH(n)] = n;

    return true;
}

uint32 Fingerprint2AQCacheHorizMult::query(uint32 i, uint32 j) {
    uint32 v = 0;
    if (i == j)
        return n - i;
    if (s[i + v] == s[j + v]) {
        v++;
        uint32 ihh = HH(i + v);
        uint32 jhh = HH(j + v);
        while (H[ihh] == H[jhh]) {
            v += t;
            ihh++;
            jhh++;
        }
        while (s[i + v] == s[j + v]) {
            v++;
        }
    }
    return v;
}

void Fingerprint2AQCacheHorizMult::cleanup() {
    delete[] H;
    s = NULL;
    n = 0;
    H = NULL;
    t = 0;
    ndt = 0;
}

void Fingerprint2AQCacheHorizMult::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_2<%s>ac_{cache-horizontal-mult}", f->name);
}

uint64 Fingerprint2AQCacheHorizMult::spaceUsage(uint32 n) {
    uint32 t = f->f(n);
    if (t < 1)
        t = 1;

    uint32 ndt = (n+1+t)/t;

    uint32 max = (t - 1)*ndt + n/t;
    return sizeof(Fingerprint2AQCacheHorizMult) + (max+1)*sizeof(uint32);
}
