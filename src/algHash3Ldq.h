#ifndef _ALGHASH3LDQ_H_
#define _ALGHASH3LDQ_H_

#include "algHash3L.h"

class Fingerprint3AQ : public Fingerprint3W {
public:
    virtual uint32 query(uint32, uint32);
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint3AQ(NamedFunc*, NamedFunc*);
    ~Fingerprint3AQ();
};

#endif
