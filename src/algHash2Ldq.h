#ifndef _ALGHASH2LDQ_H_
#define _ALGHASH2LDQ_H_

#include "algHash.h"

class Fingerprint2AQ : public Fingerprint2W {
public:
    virtual uint32 query(uint32, uint32);
    virtual void getName(char*, uint32);

    Fingerprint2AQ(NamedFunc*);
    ~Fingerprint2AQ();
};

#endif
