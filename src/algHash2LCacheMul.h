#ifndef _ALGHASH2LCACNEMUL_H_
#define _ALGHASH2LCACNEMUL_H_

#include "algorithm.h"

class Fingerprint2AQCacheHorizMult : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint2AQCacheHorizMult(NamedFunc*);
    ~Fingerprint2AQCacheHorizMult();

protected:
    uint8* s;
    uint32 n;
    uint32* H;
    uint32 t;
    uint32 ndt;
    NamedFunc* f;
};

#endif
