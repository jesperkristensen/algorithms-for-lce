#include "algHash2LCache.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint2AQCacheHorizShift::Fingerprint2AQCacheHorizShift(NamedFunc* f) {
    s = NULL;
    n = 0;
    H = NULL;
    t = 0;
    this->f = f;
    S_CLEAR(t)
    S_CLEAR(ndt);
}

// H[(i mod t)*ndt + i div t]
#define HH(i) S_MUL(S_MOD(i, t), ndt) + S_DIV(i, t)

Fingerprint2AQCacheHorizShift::~Fingerprint2AQCacheHorizShift() {
}

bool Fingerprint2AQCacheHorizShift::preproc(TestString* ts) {
    s = ts->s;
    n = ts->n;

    t = f->f(n);
    if (t < 1)
        t = 1;
    S_PREP_MOD(t)

    // ndt = ceil((n+1)/t)
    uint32 ndt = (n+1+t)/t;
    S_PREP(ndt)

    uint32 max = S_MUL(t - 1, ndt) + S_DIV(n, t);

    H = new (std::nothrow) uint32[max+1];
    if (!H) {
        s = NULL;
        n = 0;
        t = 0;
        S_CLEAR(t)
        S_CLEAR(ndt)
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

uint32 Fingerprint2AQCacheHorizShift::query(uint32 i, uint32 j) {
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

void Fingerprint2AQCacheHorizShift::cleanup() {
    delete[] H;
    s = NULL;
    n = 0;
    H = NULL;
    t = 0;
    S_CLEAR(t)
    S_CLEAR(ndt)
}

void Fingerprint2AQCacheHorizShift::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_2<%s>ac_{cache-horizontal-shift}", f->name);
}

uint64 Fingerprint2AQCacheHorizShift::spaceUsage(uint32 n) {
    uint32 t = f->f(n);
    if (t < 1)
        t = 1;
    S_DECL(t)
    S_PREP(t)

    uint32 ndt = (n+1+t)/t;
    S_DECL(ndt)
    S_PREP(ndt)

    uint32 max = S_MUL(t - 1, ndt) + S_DIV(n, t);
    return sizeof(Fingerprint2AQCacheHorizShift) + (max+1)*sizeof(uint32);
}
