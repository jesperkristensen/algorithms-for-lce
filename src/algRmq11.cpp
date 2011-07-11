#include "algRmq11.h"

#include <stdio.h>
#include <new>
#include <math.h>

AlgorithmRmq11::AlgorithmRmq11() {
}

AlgorithmRmq11::~AlgorithmRmq11() {
}

void AlgorithmRmq11::getName(char* name, uint32 size) {
    snprintf(name, size, "DirectComp<1>RMQ<n;1>");
}

/*uint64 AlgorithmRmq11::spaceUsage(uint32 n) {
    return sizeof(AlgorithmRmq1) + (-100); // TODO find out how to measure the RMQ structure
}*/

uint32 AlgorithmRmq11::query(uint32 i, uint32 j) {
    if (s->s[i] != s->s[j])
        return 0;

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

/*
bool AlgorithmRmq11::preproc(TestString* s) {
}

void AlgorithmRmq11::cleanup() {
}
*/
