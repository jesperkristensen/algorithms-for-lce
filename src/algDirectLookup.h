#ifndef _ALGDIRECTLOOKUP_H_
#define _ALGDIRECTLOOKUP_H_

#include "algorithm.h"
class AlgorithmDirectLookup : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmDirectLookup();
    ~AlgorithmDirectLookup();

protected:
    uint32* table;
    uint32 n;
    uint32 sham;
};

#endif
