#ifndef _ALGHASH2LCACNE_H_
#define _ALGHASH2LCACNE_H_

#include "algorithm.h"
#include "bittricks.h"

class Fingerprint2AQCacheHorizShift : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint2AQCacheHorizShift(NamedFunc*);
    ~Fingerprint2AQCacheHorizShift();

protected:
    uint8* s;
    uint32 n;
    uint32* H;
    uint32 t;
    S_DECL_MOD(t)
    S_DECL(ndt)
    NamedFunc* f;
};

#endif
