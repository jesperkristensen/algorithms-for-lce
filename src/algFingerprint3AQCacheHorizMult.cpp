#include "algFingerprint3AQCacheHorizMult.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint3AQCacheHorizMult::Fingerprint3AQCacheHorizMult(NamedFunc* f1, NamedFunc* f2) {
    s = NULL;
    n = 0;
    H1 = NULL;
    H2 = NULL;
    t1 = 0;
    t2 = 0;
    this->f1 = f1;
    this->f2 = f2;
    ndt1 = 0;
    ndt2 = 0;
}

// H[(i mod t)*ndt + i div t]
#define HH1(i) ((i)%t1)*ndt1 + (i)/t1
#define HH2(i) ((i)%t2)*ndt2 + (i)/t2

Fingerprint3AQCacheHorizMult::~Fingerprint3AQCacheHorizMult() {
}

bool Fingerprint3AQCacheHorizMult::preproc(TestString* ts) {
    s = ts->s;
    n = ts->n;

    t1 = f1->f(n);
    t2 = f2->f(n);
    if (t1 < 1)
        t1 = 1;
    if (t2 < t1)
        t2 = t1;

    // ndt = ceil((n+1)/t)
    ndt1 = (n+1+t1)/t1;
    ndt2 = (n+1+t2)/t2;

    uint32 max1 = (t1 - 1) * ndt1 + n / t1;
    uint32 max2 = (t2 - 1) * ndt2 + n / t2;

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
        ndt1 = 0;
        ndt2 = 0;
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

uint32 Fingerprint3AQCacheHorizMult::query(uint32 i, uint32 j) {
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

void Fingerprint3AQCacheHorizMult::cleanup() {
    delete[] H1;
    delete[] H2;
    s = NULL;
    n = 0;
    H1 = NULL;
    H2 = NULL;
    t1 = 0;
    t2 = 0;
    ndt1 = 0;
    ndt2 = 0;
}

void Fingerprint3AQCacheHorizMult::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_3<%s;%s>ac_{cache-horizontal-mult}", f1->name, f2->name);
}

uint64 Fingerprint3AQCacheHorizMult::spaceUsage(uint32 n) {
    uint32 t1 = f1->f(n);
    uint32 t2 = f2->f(n);
    if (t1 < 1)
        t1 = 1;
    if (t2 < t1)
        t2 = t1;

    uint32 ndt1 = (n+1+t1)/t1;
    uint32 ndt2 = (n+1+t1)/t1;

    uint32 max1 = (t1 - 1) * ndt1 + n / t1;
    uint32 max2 = (t2 - 1) * ndt2 + n / t2;
    return sizeof(Fingerprint3AQCacheHorizMult) + (max1+1+max2+1)*sizeof(uint32);
}
