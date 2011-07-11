#ifndef _ALGHASH_H_
#define _ALGHASH_H_

#include "algorithm.h"

class Fingerprint2W : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint2W(NamedFunc*);
    ~Fingerprint2W();

protected:
    uint8* s;
    uint32 n;
    uint32* H;
    uint32 t;
    NamedFunc* f;
};

#endif
