#include "algFingerprint3AQCacheHorizShift.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint3AQCacheHorizShift::Fingerprint3AQCacheHorizShift(NamedFunc* f1, NamedFunc* f2) {
    s = NULL;
    n = 0;
    H1 = NULL;
    H2 = NULL;
    t1 = 0;
    t2 = 0;
    this->f1 = f1;
    this->f2 = f2;
    S_CLEAR(t1)
    S_CLEAR(t2)
    S_CLEAR(ndt1);
    S_CLEAR(ndt2);
}

// H[(i mod t)*ndt + i div t]
#define HH1(i) S_MUL(S_MOD(i, t1), ndt1) + S_DIV(i, t1)
#define HH2(i) S_MUL(S_MOD(i, t2), ndt2) + S_DIV(i, t2)

Fingerprint3AQCacheHorizShift::~Fingerprint3AQCacheHorizShift() {
}

bool Fingerprint3AQCacheHorizShift::preproc(TestString* ts) {
    s = ts->s;
    n = ts->n;

    t1 = f1->f(n);
    t2 = f2->f(n);
    if (t1 < 1)
        t1 = 1;
    if (t2 < t1)
        t2 = t1;
    S_PREP_MOD(t1)
    S_PREP_MOD(t2)

    // ndt = ceil((n+1)/t)
    uint32 ndt1 = (n+1+t1)/t1;
    uint32 ndt2 = (n+1+t2)/t2;
    S_PREP(ndt1)
    S_PREP(ndt2)

    uint32 max1 = S_MUL(t1 - 1, ndt1) + S_DIV(n, t1);
    uint32 max2 = S_MUL(t2 - 1, ndt2) + S_DIV(n, t2);

    H1 = new (std::nothrow) uint32[max1+1];
    H2 = new (std::nothrow) uint32[max2+1];
    if (!H1 || !H2) {
        if (H1) {
            delete[] H1;
            H1 = NULL;
        }
        if (H2) {
            delete[] H2;
            H2 = NULL;
        }
        s = NULL;
        n = 0;
        t1 = 0;
        t2 = 0;
        S_CLEAR(t1)
        S_CLEAR(t2)
        S_CLEAR(ndt1)
        S_CLEAR(ndt2)
        return false;
    }

    uint32 h1;
    uint32 h2;
    // loop through each suffix s->sa[i] in sorted order.
    for (uint32 i = 0; i < n; i++) {
        // if suffix s->sa[i] does not have a prefix of length t in common with its predecessor, then update the current hash
        if (ts->lcp[i] < t1)
            h1 = i;
        if (ts->lcp[i] < t2)
            h2 = i;
        H1[HH1(ts->sa[i])] = h1;
        H2[HH2(ts->sa[i])] = h2;
    }
    H1[HH1(n)] = n;
    H2[HH2(n)] = n;

    return true;
}

uint32 Fingerprint3AQCacheHorizShift::query(uint32 i, uint32 j) {
    uint32 v = 0;
    if (i == j)
        return n - i;
    if (s[i + v] == s[j + v]) {
        v++;
        if (H1[HH1(i + v)] == H1[HH1(j + v)]) {
            v += t1;
            uint32 ihh = HH2(i + v);
            uint32 jhh = HH2(j + v);
            while (H2[ihh] == H2[jhh]) {
                v += t2;
                ihh++;
                jhh++;
            }
            ihh = HH1(i + v);
            jhh = HH1(j + v);
            while (H1[ihh] == H1[jhh]) {
                v += t1;
                ihh++;
                jhh++;
            }
        }
        while (s[i + v] == s[j + v]) {
            v++;
        }
    }
    return v;
}

void Fingerprint3AQCacheHorizShift::cleanup() {
    delete[] H1;
    delete[] H2;
    s = NULL;
    n = 0;
    H1 = NULL;
    H2 = NULL;
    t1 = 0;
    t2 = 0;
    S_CLEAR(t1)
    S_CLEAR(t2)
    S_CLEAR(ndt1)
    S_CLEAR(ndt2)
}

void Fingerprint3AQCacheHorizShift::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_3<%s;%s>ac_{cache-horizontal-shift}", f1->name, f2->name);
}

uint64 Fingerprint3AQCacheHorizShift::spaceUsage(uint32 n) {
    uint32 t1 = f1->f(n);
    uint32 t2 = f2->f(n);
    if (t1 < 1)
        t1 = 1;
    if (t2 < t1)
        t2 = t1;
    S_DECL(t1)
    S_DECL(t2)
    S_PREP(t1)
    S_PREP(t2)

    uint32 ndt1 = (n+1+t1)/t1;
    uint32 ndt2 = (n+1+t1)/t1;
    S_DECL(ndt1)
    S_DECL(ndt2)
    S_PREP(ndt1)
    S_PREP(ndt2)

    uint32 max1 = S_MUL(t1 - 1, ndt1) + S_DIV(n, t1);
    uint32 max2 = S_MUL(t2 - 1, ndt2) + S_DIV(n, t2);
    return sizeof(Fingerprint3AQCacheHorizShift) + (max1+1+max2+1)*sizeof(uint32);
}
