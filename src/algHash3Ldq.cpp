#include "algHash3Ldq.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint3AQ::Fingerprint3AQ(
        NamedFunc* f2,
        NamedFunc* f1)
        : Fingerprint3W(f2, f1) {
}

Fingerprint3AQ::~Fingerprint3AQ() {
}

uint32 Fingerprint3AQ::query(uint32 i, uint32 j) {
    uint32 v = 0;
    if (i == j)
        return n - i;
    if (s[i + v] == s[j + v]) {
        v++;
        if (H1[i + v] == H1[j + v]) {
            v += t1;
            while (H2[i + v] == H2[j + v])
                v += t2;
            while (H1[i + v] == H1[j + v])
                v += t1;
        }
        while (s[i + v] == s[j + v])
            v++;
    }
    return v;
}

void Fingerprint3AQ::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_3<%s;%s>ac", f2->name, f1->name);
}

uint64 Fingerprint3AQ::spaceUsage(uint32 n) {
    return sizeof(Fingerprint3AQ) - sizeof(Fingerprint3W) + Fingerprint3W::spaceUsage(n);
}
