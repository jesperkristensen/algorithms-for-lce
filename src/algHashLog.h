#ifndef _ALGHASHLOG_H_
#define _ALGHASHLOG_H_

#include "algorithm.h"

class FingerprintLW : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    FingerprintLW();
    ~FingerprintLW();

protected:
    uint8* s;
    uint32 n;
    uint32* H;
    uint32 k;
};

#endif
