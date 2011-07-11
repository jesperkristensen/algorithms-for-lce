#ifndef _ALGDIRECTCOMP_H_
#define _ALGDIRECTCOMP_H_

#include "algorithm.h"
class AlgorithmDirectComp : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmDirectComp();
    ~AlgorithmDirectComp();

protected:
    TestString* s;
};

#endif
