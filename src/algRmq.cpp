#include "algRmq.h"

#include <stdio.h>
#include <new>

#include "RMQ_n_logn/RMQ_1_n.hpp"
#include "RMQ_n_logn/RMQ_n_1_improved.hpp"
#include "RMQ_n_logn/RMQ_n_logn_2.hpp"
#include "RMQ_n_logn/RMQ_n_logn_4.hpp"
//#include "RMQ_n_logn/RMQ_nlogn_1.hpp"
#include "RMQ_n_logn/RMQ_succinct.hpp"
#include "RMQ_n_logn/RMQ_n_logn.hpp"
//#include "jf/optimalRMQ/optimalRMQ.hpp"

AlgorithmRmq::AlgorithmRmq(enum RMQ_ALG alg) {
    this->s = NULL;
    this->rmq = NULL;
    this->alg = alg;
}

AlgorithmRmq::~AlgorithmRmq() {
}

bool AlgorithmRmq::preproc(TestString* s) {
    this->s = s;

    switch (alg) {
    case RMQ_1_N:
        this->rmq = new (std::nothrow) RMQ_1_n((int*)s->lcp, s->n);
        break;
    case RMQ_N_1:
        this->rmq = new (std::nothrow) RMQ_n_1_improved((int*)s->lcp, s->n);
        break;
    case RMQ_N_LOGN_2:
        this->rmq = new (std::nothrow) RMQ_n_logn_2((int*)s->lcp, s->n);
        break;
    case RMQ_N_LOGN_4:
        this->rmq = new (std::nothrow) RMQ_n_logn_4((int*)s->lcp, s->n);
        break;
    //case RMQ_NLOGN_1:
    //    d->rmq = new RMQ_nlogn_1((int*)s->lcp, ???, s->n);
    //    break;
    case RMQ_SUCCINCT:
        this->rmq = new (std::nothrow) RMQ_succinct((int*)s->lcp, s->n);
        break;
    case RMQ_N_LOGN_D2:
        this->rmq = new (std::nothrow) RMQ_n_logn((int*)s->lcp, s->n, 2);
        break;
    case RMQ_N_LOGN_D4:
        this->rmq = new (std::nothrow) RMQ_n_logn((int*)s->lcp, s->n, 4);
        break;
    case RMQ_OPTIMAL:
        //this->rmq = new (std::nothrow) RMQ_optimal((int*)s->lcp, s->n);
        break;
    }
    if (!this->rmq) {
        this->s = NULL;
        return false;
    }

    return true;
}

uint32 AlgorithmRmq::query(uint32 i, uint32 j) {
    TestString* s = this->s;
    uint32 min;

    if (i == j)
        return s->n - i;

    i = s->sainv[i];
    j = s->sainv[j];

    if (i > j) {
        min = i;
        i = j;
        j = min;
    }

    return s->lcp[this->rmq->query(i + 1, j)];
}

void AlgorithmRmq::cleanup() {
    delete this->rmq;
    this->s = NULL;
    this->rmq = NULL;
}

const char* const rmqAlgNames[] = {"1;n", "n;1", "n;2log n", "n;4log n", "succinct;?", "n;(2)log n", "n;(4)log n", "optimal"};

void AlgorithmRmq::getName(char* name, uint32 size) {
    snprintf(name, size, "RMQ<%s>_{virtual}", rmqAlgNames[this->alg]);
}

uint64 AlgorithmRmq::spaceUsage(uint32 n) {
    return sizeof(AlgorithmRmq) + (uint64)1e8; // TODO find out how to measure the RMQ structure
}
