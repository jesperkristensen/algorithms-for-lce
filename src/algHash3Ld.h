#ifndef _ALGHASH3LD_H_
#define _ALGHASH3LD_H_

#include "algHash3L.h"

class Fingerprint3AP : public Fingerprint3W {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    Fingerprint3AP(NamedFunc*, NamedFunc*, NamedFunc*, NamedFunc*);
    ~Fingerprint3AP();

protected:
    uint32 td0;
    NamedFunc* fd0;
    uint32 td1;
    NamedFunc* fd1;
};

#endif
