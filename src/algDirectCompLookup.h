#ifndef _ALGDIRECTCOMPLOOKUP_H_
#define _ALGDIRECTCOMPLOOKUP_H_

#include "algorithm.h"
#include "bittricks.h"

class AlgorithmDirectCompLookup : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmDirectCompLookup(NamedFunc*);
    AlgorithmDirectCompLookup(NamedFunc*, uint32);
    ~AlgorithmDirectCompLookup();

protected:
    uint8* s;
    uint32* table;
    uint32 n;
    S_DECL(nn)
    S_DECL_MOD(t)
    NamedFunc* f;
    uint32 fp;
};

#endif
