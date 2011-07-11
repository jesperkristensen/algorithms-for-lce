#ifndef _ALGHASHLOGD_H_
#define _ALGHASHLOGD_H_

#include "algHashLog.h"

class FingerprintLA : public FingerprintLW {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);

    FingerprintLA();
    ~FingerprintLA();
};

#endif
