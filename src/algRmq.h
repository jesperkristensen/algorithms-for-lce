#ifndef _ALGRMQ_H_
#define _ALGRMQ_H_

#include "algorithm.h"
#include "RMQ_n_logn/RMQ.hpp"
enum RMQ_ALG { RMQ_1_N, RMQ_N_1, RMQ_N_LOGN_2, RMQ_N_LOGN_4/*, RMQ_NLOGN_1*/, RMQ_SUCCINCT, RMQ_N_LOGN_D2, RMQ_N_LOGN_D4, RMQ_OPTIMAL};

class AlgorithmRmq : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmRmq(enum RMQ_ALG);
    ~AlgorithmRmq();

protected:
    TestString* s;
    RMQ* rmq;
    enum RMQ_ALG alg;
};

#endif
