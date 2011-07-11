#include "algHash3L.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

// http://cmph.sourceforge.net/
// #include "cmph-1.0/src/cmph.h"

Fingerprint3W::Fingerprint3W(NamedFunc* f2, NamedFunc* f1) {
    this->s = NULL;
    this->n = 0;
    this->H1 = NULL;
    this->t1 = 0;
    this->f1 = f1;
    this->H2 = NULL;
    this->t2 = 0;
    this->f2 = f2;
}

Fingerprint3W::~Fingerprint3W() {
}

bool Fingerprint3W::preproc(TestString* s) {
    uint32 t1 = this->f1->f(s->n);
    uint32 t2 = this->f2->f(s->n);
    if (t1 < 1)
        t1 = 1;
    if (t2 < t1)
        t2 = t1;

    this->H1 = new (std::nothrow) uint32[s->n+1];
    if (!this->H1) {
        return false;
    }
    this->H2 = new (std::nothrow) uint32[s->n+1];
    if (!this->H2) {
        delete[] this->H1;
        this->H1 = NULL;
        return false;
    }
    this->s = s->s;
    this->n = s->n;
    this->t1 = t1;
    this->t2 = t2;

    uint32 h1, h2;
    // loop through each suffix s->sa[i] in sorted order.
    for (uint32 i = 0; i < s->n; i++) {
        // if suffix s->sa[i] does not have a prefix of length t in common with its predecessor, then update the current hash
        if (s->lcp[i] < t1)
            h1 = i;
        if (s->lcp[i] < t2)
            h2 = i;
        this->H1[s->sa[i]] = h1;
        this->H2[s->sa[i]] = h2;
    }
    this->H1[s->n] = s->n;
    this->H2[s->n] = s->n;

    return true;
}

uint32 Fingerprint3W::query(uint32 i, uint32 j) {
    uint32 t = 0;
    if (i == j)
        return this->n - i;
    while (this->H2[i + t] == this->H2[j + t]) {
        t += this->t2;
    }
    while (this->H1[i + t] == this->H1[j + t]) {
        t += this->t1;
    }
    while (this->s[i + t] == this->s[j + t]) {
        t++;
    }
    return t;
}

void Fingerprint3W::cleanup() {
    delete[] this->H1;
    delete[] this->H2;
    this->s = NULL;
    this->n = 0;
    this->H1 = NULL;
    this->H2 = NULL;
    this->t1 = 0;
    this->t2 = 0;
}

void Fingerprint3W::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_3<%s;%s>wc", this->f2->name, this->f1->name);
}

uint64 Fingerprint3W::spaceUsage(uint32 n) {
    return sizeof(Fingerprint3W) + 2*(n+1)*sizeof(uint32);
}
