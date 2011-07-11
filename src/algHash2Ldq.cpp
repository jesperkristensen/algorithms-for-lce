#include "algHash2Ldq.h"
#include <stdlib.h>
#include <stdio.h>

Fingerprint2AQ::Fingerprint2AQ(NamedFunc* f) : Fingerprint2W(f) {
}

Fingerprint2AQ::~Fingerprint2AQ() {
}

uint32 Fingerprint2AQ::query(uint32 i, uint32 j) {
    uint32 v = 0;
    if (i == j)
        return n - i;
    if (s[i + v] == s[j + v]) {
        while (H[i + v] == H[j + v])
            v += t;
        while (s[i + v] == s[j + v])
            v++;
    }
    return v;
}

void Fingerprint2AQ::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_2<%s>ac", f->name);
}
