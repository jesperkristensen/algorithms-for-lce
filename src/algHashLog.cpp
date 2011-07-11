#include "algHashLog.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <math.h>

FingerprintLW::FingerprintLW() {
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->k = 0;
}

FingerprintLW::~FingerprintLW() {
}

bool FingerprintLW::preproc(TestString* s) {
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
            H[s->sa[i]] = h;
        }
        H[n] = n;
        H += n+1;
    }

    return true;
}

uint32 FingerprintLW::query(uint32 i, uint32 j) {
    if (i == j)
        return this->n - i;
    uint32 t = 0;
    uint32* H = this->H;
    for (int32 c = k-1; c >= 0; c--) {
        H -= (n+1);
        if (H[i + t] == H[j + t])
            t += 1<<c;
    }
    return t;
}

void FingerprintLW::cleanup() {
    H -= k*(n+1);
    delete[] this->H;
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->k = 0;
}

void FingerprintLW::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_{log n}wc");
}

uint64 FingerprintLW::spaceUsage(uint32 n) {
    uint32 k = (uint32) ceil(log2(n+1));
    return sizeof(FingerprintLW) + (n+1)*k*sizeof(uint32);
}
