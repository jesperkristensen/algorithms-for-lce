#ifndef _RMQ_n_logn_hpp_
#define _RMQ_n_logn_hpp_

#include "RMQ.hpp"
#include "RMQ_nlogn_1.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

class RMQ_n_logn : public RMQ {
public:
	// liefert RMQ[i,j]
	virtual DTidx query(DTidx, DTidx);

	// returns space occupied by the index (in bytes)
	//virtual unsigned long getSize();

	// this constructor divides the array into blocks of size log(n)
	RMQ_n_logn(DT* a, DTidx n);

	// this constructor divides the array into blocks of size log(n)/d
	RMQ_n_logn(DT* a, DTidx n, float d);

	virtual ~RMQ_n_logn();

protected:
	// array
	DT *a;

	// index array for the out-of-block queries (contains indices of block-minima)
	DTidx *c;

	// size of array a
	DTidx n;

	// block size
	DTidx bs;

	// number of blocks (always n/bs)
	DTidx nb;

	// return block of entry i:
	inline DTidx block(DTidx i) { return i/bs; }

	// nlogn_1-Algo for out-of-block-block-queries:
	RMQ_nlogn_1* RMQ_ST;

	// count allocated memory:
	unsigned long mem;
};

#endif
