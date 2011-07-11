#ifndef _ALGRMQN_H_
#define _ALGRMQN_H_

#include "algorithm.h"
class AlgorithmRmqN : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmRmqN();
    ~AlgorithmRmqN();

protected:
    TestString* s;
};

#endif
