#include "algHashLogDCache.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <math.h>

FingerprintLACacheVertiMult::FingerprintLACacheVertiMult() {
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->k = 0;
}

FingerprintLACacheVertiMult::~FingerprintLACacheVertiMult() {
}

bool FingerprintLACacheVertiMult::preproc(TestString* s) {
    uint32 k = (uint32) ceil(log2(s->n+1));

    H = new (std::nothrow) uint32[(s->n+1)*k];
    if (!H) {
        return false;
    }
    this->s = s->s;
    this->n = s->n;
    this->k = k;

    uint32 h;
    for (uint32 c = 0; c < k; c++) {
        // loop through each suffix s->sa[i] in sorted order.
        for (uint32 i = 0; i < n; i++) {
            // if suffix s->sa[i] does not have a prefix of length 1<<c in common with its predecessor, then update the current hash
            if (s->lcp[i] < 1<<c)
                h = i;
            H[c + (s->sa[i])*k] = h;
        }
        H[c + n*k] = n;
    }

    return true;
}

uint32 FingerprintLACacheVertiMult::query(uint32 i, uint32 j) {
    if (i == j)
        return this->n - i;
    uint32 t = 0;
    int32 c;
    for (c = 0; c < k; c++) {
        if (H[c + (i + t)*k] == H[c + (j + t)*k])
            t += 1<<c;
        else break;
    }
    for (c--; c >= 0; c--) {
        if (H[c + (i + t)*k] == H[c + (j + t)*k])
            t += 1<<c;
    }
    return t;
}

void FingerprintLACacheVertiMult::cleanup() {
    delete[] this->H;
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->k = 0;
}

void FingerprintLACacheVertiMult::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_{log n}ac_{cache-vertical-mult}");
}

uint64 FingerprintLACacheVertiMult::spaceUsage(uint32 n) {
    uint32 k = (uint32) ceil(log2(n+1));
    return sizeof(FingerprintLACacheVertiMult) + (n+1)*k*sizeof(uint32);
}
