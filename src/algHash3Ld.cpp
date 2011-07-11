#include "algHash3Ld.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>

Fingerprint3AP::Fingerprint3AP(
        NamedFunc* fd0,
        NamedFunc* fd1,
        NamedFunc* f2,
        NamedFunc* f1)
        : Fingerprint3W(f2, f1) {
    this->td0 = 0;
    this->fd0 = fd0;
    this->td1 = 0;
    this->fd1 = fd1;
}

Fingerprint3AP::~Fingerprint3AP() {
}

bool Fingerprint3AP::preproc(TestString* s) {
    if (!Fingerprint3W::preproc(s))
        return false;
    td0 = fd0->f(s->n);
    if (td0 < 1)
        td0 = 1;
    td1 = fd1->f(s->n);
    if (td1 < td0)
        td1 = td0;
    return true;
}

uint32 Fingerprint3AP::query(uint32 i, uint32 j) {
    uint32 t = 0;
    if (i == j)
        return this->n - i;

    while (this->s[i + t] == this->s[j + t] && t < this->td0)
        t++;
    if (t >= this->td0) {

        while (this->H1[i + t] == this->H1[j + t] && t < this->td1)
            t += this->t1;
        if (t >= this->td1) {

            while (this->H2[i + t] == this->H2[j + t])
                t += this->t2;

            while (this->H1[i + t] == this->H1[j + t])
                t += this->t1;
        }

        while (this->s[i + t] == this->s[j + t])
            t++;
    }
    return t;
}

void Fingerprint3AP::cleanup() {
    Fingerprint3W::cleanup();
    td0 = 0;
    td1 = 0;
}

void Fingerprint3AP::getName(char* name, uint32 size) {
    snprintf(name, size, "Fingerprint_3<%s;%s>ac<%s;%s>", this->f2->name, this->f1->name, this->fd0->name, this->fd1->name);
}

uint64 Fingerprint3AP::spaceUsage(uint32 n) {
    return sizeof(Fingerprint3AP) - sizeof(Fingerprint3W) + Fingerprint3W::spaceUsage(n);
}
