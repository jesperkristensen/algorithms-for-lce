#ifndef _ALGHASH3L_H_
#define _ALGHASH3L_H_

#include "algorithm.h"

class Fingerprint3W : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint3W(NamedFunc*, NamedFunc*);
    ~Fingerprint3W();

protected:
    uint8* s;
    uint32 n;
    uint32* H1;
    uint32 t1;
    NamedFunc* f1;
    uint32* H2;
    uint32 t2;
    NamedFunc* f2;
};

#endif
