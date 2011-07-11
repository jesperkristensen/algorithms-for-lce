#include "algRmq1.h"

#include <stdio.h>
#include <new>
#include <math.h>

AlgorithmRmq1::AlgorithmRmq1() {
}

AlgorithmRmq1::~AlgorithmRmq1() {
}

void AlgorithmRmq1::getName(char* name, uint32 size) {
    snprintf(name, size, "RMQ<n;1>");
}

uint64 AlgorithmRmq1::spaceUsage(uint32 n) {
    uint32 bs = (uint32) ceil(log2(n) / 4);
    uint32 nb = (n-1)/bs+1;
    uint32 qpb = bs * (bs+1) / 2;
    // log part
    uint32 depth = log2fast(nb);

    return sizeof(AlgorithmRmq1)
        + n*sizeof(uint32) // sainv
        + n*sizeof(uint32) // a
        + sizeof(uint32)*nb // c
        + sizeof(uint32)*nb // type
        + sizeof(uint32*)*Catalan[bs][bs] // Prec
        + sizeof(uint32)*qpb*Catalan[bs][bs] // Prec[i]
        // log part
        + sizeof(uint32*)*depth // logM
        + sizeof(uint32)*nb*depth; // logM[i]

/*
    bs = ceil(log2(n) / 4);
    nb = (n-1)/bs+1;
    words = 2*n + 2*nb + (bs * (bs+1) / 2 + 1)*Catalan_bs + (nb+1)*log2fast(nb);
*/
}

const uint32 AlgorithmRmq1::Catalan[17][17] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
    {0,0,2,5,9,14,20,27,35,44,54,65,77,90,104,119,135},
    {0,0,0,5,14,28,48,75,110,154,208,273,350,440,544,663,798},
    {0,0,0,0,14,42,90,165,275,429,637,910,1260,1700,2244,2907,3705},
    {0,0,0,0,0,42,132,297,572,1001,1638,2548,3808,5508,7752,10659,14364},
    {0,0,0,0,0,0,132,429,1001,2002,3640,6188,9996,15504,23256,33915,48279},
    {0,0,0,0,0,0,0,429,1430,3432,7072,13260,23256,38760,62016,95931,144210},
    {0,0,0,0,0,0,0,0,1430,4862,11934,25194,48450,87210,149226,245157,389367},
    {0,0,0,0,0,0,0,0,0,4862,16796,41990,90440,177650,326876,572033,961400},
    {0,0,0,0,0,0,0,0,0,0,16796,58786,149226,326876,653752,1225785,2187185},
    {0,0,0,0,0,0,0,0,0,0,0,58786,208012,534888,1188640,2414425,4601610},
    {0,0,0,0,0,0,0,0,0,0,0,0,208012,742900,1931540,4345965,8947575},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,742900,2674440,7020405,15967980},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2674440,9694845,25662825},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9694845,35357670},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35357670}
};

const int32 AlgorithmRmq1::minus_infinity = -1;//-2147483648;

uint32 AlgorithmRmq1::query(uint32 i, uint32 j) {
    if (i == j)
        return this->n - i;

    i = this->s->sainv[i];
    j = this->s->sainv[j];

    if (i > j) {
        uint32 m = i;
        i = j;
        j = m;
    }

    i++;


    uint32 block_i = block(i);       // block where i is
    uint32 block_j = block(j);       // j's block
    uint32 i_pos = i - (block_i*bs); // position of i in block_i
    uint32 j_pos = j - (block_j*bs); // pos. of j in block_j
    uint32 min, min_i, min_j; 		// min: to be returned

    if (block_j == block_i)
        min = (block_i*bs) + Prec[type[block_i]][i_pos*(bs-1)+j_pos-((i_pos-1)*i_pos/2)];
    else {
        min_i = (block_i*bs) + Prec[type[block_i]][(i_pos+1)*(bs-1)-((i_pos-1)*i_pos/2)];
        min_j = (block_j*bs) + Prec[type[block_j]][j_pos];
        min = a[min_i] < a[min_j] ? min_i : min_j;
        if (block_j > block_i + 1) { // out-of-block query:
            i = block_i+1;
            j = block_j-1;

            if (j-i == 0) min_i = c[j];
            else if (j-i == 1) min_i = c[logM[0][i]];
            else {
                uint32 k = log2fast(j-i);
                uint32 twotothek = 1 << k; // 2^k
                min_i = c[loga[logc[logM[k-1][i]]] <= loga[logc[logM[k-1][j+1-twotothek]]] ? logM[k-1][i] : logM[k-1][j+1-twotothek]];
            }
            if (a[min_i] < a[min]) min = min_i;
        }
    }

    return s->lcp[min];
}

/**
 * Standard Constructor. a is the array to be prepared for RMQ.
 * n is the size of the array.
 */
bool AlgorithmRmq1::preproc(TestString* s) {
    this->s = s;
    int32* a = (int32*) s->lcp;
    uint32 n = s->n;


    this->a = a;
    this->n = n;
    bs = (uint32) ceil(log2(n) / 4); // calculate block size
    nb = block(n-1)+1;              // number of blocks
    qpb = bs * (bs+1) / 2;          // # of different queries per block

    // allocate and fill arrays for out-of-block-queries;
    // combined with type-calculation for the blocks:
    c = new uint32[nb];
    type = new uint32[nb];
    Prec = new uint32*[Catalan[bs][bs]];
    for (uint32 i = 0; i < Catalan[bs][bs]; i++) {
        Prec[i] = new uint32[qpb];
        Prec[i][0] = bs; // init with impossible value
    }
    int32* rp = new int32[bs+1];  // rp: rightmost path in Cart. tree

    uint32 min;   // position of minimum in current block
    uint32 z=0;   // index in array a
    uint32 end;   // end of current block
    uint32 start; // start of current block
    uint32 q;     // position in Catalan triangle
    uint32 p;     // --------- " ----------------
    rp[0] = minus_infinity; // stopper (minus infinity)

    for (uint32 i = 0; i < nb; i++) { // step through blocks
        start = z;            // init start
        min = start;          // init minimum
        end = start + bs;     // end of block
        if (end > n) end = n; // last block could be smaller than bs!
        q = bs;       // init q
        p = bs-1;     // init p
        type[i] = 0;  // init type (will be increased!)
        rp[1] = a[z]; // init rightmost path

        while (++z < end) {   // step through current block:
            if (a[z] < a[min]) min = z;   // update minimum
            p--;
            while (rp[q-p-1] > a[z]) {
                type[i] += Catalan[p][q]; // update type
                q--;
            }
            rp[q-p] = a[z]; // add last element to rightmost path
        }
        c[i] = min; // store index of minimum

        // precompute in-block-queries for this block (if necessary):
        if (Prec[type[i]][0] == bs) {
            p = 0; // now index in Prec[type[i]]
            for (uint32 j = start; j < end; j++) {
                min = j;
                for (uint32 k = j; k < end; k++) {
                    if (a[k] < a[min]) min = k;
                    Prec[type[i]][p++] = min-start;
                }
            }
        }
    }
    delete[] rp;

    logpreproc(a, c, nb); // construct sparse table on block-minima
    return true; // TODO check OOM
}

/**
 * Destructor. Deletes allocated space.
 */
void AlgorithmRmq1::cleanup() {
    logcleanup();
    delete[] type;
    delete[] c;
    for (uint32 i = 0; i < Catalan[bs][bs]; i++)
        delete[] Prec[i];
    delete[] Prec;
}





const char AlgorithmRmq1::LogTable256[256] = 
	{
		0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
	};

uint32 AlgorithmRmq1::log2fast(uint32 v) {
	uint32 c = 0;          // c will be lg(v)
	register uint32 t, tt; // temporaries

	if (tt = v >> 16)
		c = (t = v >> 24) ? 24 + LogTable256[t] : 16 + LogTable256[tt & 0xFF];
	else 
		c = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
	return c;
}

/**
 * Standard Constructor. a[c[0]],...,a[c[n-1]] is the array to be prepared for RMQ.
 * n is the size of the index array c.
 */
void AlgorithmRmq1::logpreproc(int32* a, uint32* c, uint32 n) {

	this->loga = a;
	this->logc = c;
	this->logn = n;
	uint32 depth = log2fast(n); // table depth
	logdepth = depth;

	// allocate space for table:
	uint32** M = new uint32*[depth];
    logM = M;
	for (uint32 i = 0; i < depth; i++)
		M[i] = new uint32[n];

	// fill table:
	for (uint32 i = 0; i < n-1; i++) // fill first row
		M[0][i] = a[c[i]] <= a[c[i+1]] ? i : i+1;
	if (depth > 0) M[0][n-1] = n-1;          // fill overhang in first row

	uint32 dist = 1; // always 2^j
	for (uint32 j = 1; j < depth; j++) {
		dist *= 2;
		for (uint32 i = 0; i < n - dist; i++) // fill jth row
			M[j][i] = a[c[M[j-1][i]]] <= a[c[M[j-1][i+dist]]] ? M[j-1][i] : M[j-1][i+dist];
		for (uint32 i = n - dist; i < n; i++) M[j][i] = M[j-1][i]; // overhang
	}
}

/**
 * Destructor. Deletes allocated space.
 */
void AlgorithmRmq1::logcleanup() {
	for (uint32 i = 0; i < logdepth; i++)
		delete[] logM[i];
	delete[] logM;
}

