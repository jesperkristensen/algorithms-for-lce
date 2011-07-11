#include "algHash.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

// http://cmph.sourceforge.net/
// #include "cmph-1.0/src/cmph.h"

Fingerprint2W::Fingerprint2W(NamedFunc* f) {
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->t = 0;
    this->f = f;
}

Fingerprint2W::~Fingerprint2W() {
}

bool Fingerprint2W::preproc(TestString* s) {
    uint32 t = this->f->f(s->n);
    if (t < 1)
        t = 1;

    this->H = new (std::nothrow) uint32[s->n+1];
    if (!this->H) {
        return false;
    }
    this->s = s->s;
    this->n = s->n;
    this->t = t;

    uint32 h;
    // loop through each suffix s->sa[i] in sorted order.
    for (uint32 i = 0; i < s->n; i++) {
        // if suffix s->sa[i] does not have a prefix of length t in common with its predecessor, then update the current hash
        if (s->lcp[i] < t)
            h = i;
        this->H[s->sa[i]] = h;
    }
    this->H[s->n] = s->n;

    return true;
}

uint32 Fingerprint2W::query(uint32 i, uint32 j) {
    uint32 t = 0;
    if (i == j)
        return this->n - i;
    while (this->H[i + t] == this->H[j + t]) {
        t += this->t;
    }
    while (this->s[i + t] == this->s[j + t]) {
        t++;
    }
    return t;
}

void Fingerprint2W::cleanup() {
    delete[] this->H;
    this->s = NULL;
    this->n = 0;
    this->H = NULL;
    this->t = 0;
}

void Fingerprint2W::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_2<%s>wc", this->f->name);
}

uint64 Fingerprint2W::spaceUsage(uint32 n) {
    return sizeof(Fingerprint2W) + (n+1)*sizeof(uint32);
}
