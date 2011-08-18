#ifndef _ALGFINGERPRINT3AQCACHEHORIZMULT_H_
#define _ALGFINGERPRINT3AQCACHEHORIZMULT_H_

#include "algorithm.h"
#include "bittricks.h"

class Fingerprint3AQCacheHorizMult : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint3AQCacheHorizMult(NamedFunc*, NamedFunc*);
    ~Fingerprint3AQCacheHorizMult();

protected:
    uint8* s;
    uint32 n;
    uint32 *H1, *H2;
    uint32 t1, t2, ndt1, ndt2;
    NamedFunc *f1, *f2;
};

#endif
