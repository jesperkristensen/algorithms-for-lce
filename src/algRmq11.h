#ifndef _ALGRMQ11_H_
#define _ALGRMQ11_H_

#include "algRmq1.h"

class AlgorithmRmq11 : public AlgorithmRmq1 {
public:
    //virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    //virtual void cleanup();
    virtual void getName(char*, uint32);
    //virtual uint64 spaceUsage(uint32);

    AlgorithmRmq11();
    ~AlgorithmRmq11();
};

#endif
