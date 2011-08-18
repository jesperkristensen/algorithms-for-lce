#ifndef _ALGFINGERPRINT3AQCACHEHORIZSHIFT_H_
#define _ALGFINGERPRINT3AQCACHEHORIZSHIFT_H_

#include "algorithm.h"
#include "bittricks.h"

class Fingerprint3AQCacheHorizShift : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint3AQCacheHorizShift(NamedFunc*, NamedFunc*);
    ~Fingerprint3AQCacheHorizShift();

protected:
    uint8* s;
    uint32 n;
    uint32 *H1, *H2;
    uint32 t1, t2;
    S_DECL_MOD(t1)
    S_DECL_MOD(t2)
    S_DECL(ndt1)
    S_DECL(ndt2)
    NamedFunc *f1, *f2;
};

#endif
