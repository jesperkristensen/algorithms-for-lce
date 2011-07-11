#ifndef _ALGRMQ1_H_
#define _ALGRMQ1_H_

#include "algorithm.h"

class AlgorithmRmq1 : public Algorithm {
public:
    virtual bool preproc(TestString*);
    virtual uint32 query(uint32, uint32);
    virtual void cleanup();
    virtual void getName(char*, uint32);
    virtual uint64 spaceUsage(uint32);

    AlgorithmRmq1();
    ~AlgorithmRmq1();

protected:
    TestString* s;

    // array
    int32 *a;

    // index array for the out-of-block queries (contains indices of block-minima)
    uint32 *c;

    // type of blocks
    uint32 *type;

    // precomputed in-block queries
    uint32** Prec;

    // number of different queries per block = bs*(bs+1)/2
    uint32 qpb;

    // size of array a
    uint32 n;

    // block size
    uint32 bs;

    // number of blocks (always n/bs)
    uint32 nb;

    // return block of entry i:
    inline uint32 block(uint32 i) { return i/bs; }

    // precomputed Catalan triangle (17 is enough for 64bit computing):
    static const uint32 Catalan[17][17];

    // minus infinity (change for 64bit version)
    static const int32 minus_infinity;



	void logpreproc(int32* a, uint32* c, uint32 n);

	void logcleanup();

	// the following stuff is for fast base 2 logarithms:
	// (currently only implemented for 32 bit numbers)
	static const char LogTable256[256];

	virtual uint32 log2fast(uint32);

	// array
	int32* loga;

	// index array for a:
	uint32* logc;

	// size of c
	uint32 logn;

	// depth of table
	uint32 logdepth;

	// the precomputed table:
	uint32** logM;


};

#endif
