#include "algHashLogD.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <math.h>

FingerprintLA::FingerprintLA() : FingerprintLW() {
}

FingerprintLA::~FingerprintLA() {
}

bool FingerprintLA::preproc(TestString* s) {
    if (!FingerprintLW::preproc(s))
        return false;
    H -= k*(n+1);
    return true;
}

uint32 FingerprintLA::query(uint32 i, uint32 j) {
    if (i == j)
        return this->n - i;
    uint32 t = 0;
    uint32* H = this->H;
    int32 c;
    for (c = 0; c < k; c++) {
        if (H[i + t] == H[j + t])
            t += 1<<c;
        else break;
        H += (n+1);
    }
    for (c--; c >= 0; c--) {
        H -= (n+1);
        if (H[i + t] == H[j + t])
            t += 1<<c;
    }
    return t;
}

void FingerprintLA::cleanup() {
    H += k*(n+1);
    FingerprintLW::cleanup();
}

void FingerprintLA::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_{log n}ac");
}
