#include "RMQ_n_logn.hpp"

/*unsigned long RMQ_n_logn::getSize() {
	return mem + RMQ_ST->getSize();
}*/

DTidx RMQ_n_logn::query(DTidx i, DTidx j) {
	DTidx block_i = block(i);       // block where i is
	DTidx block_j = block(j);       // j's block
	DTidx min, tmp;	                // min: to be returned

	if (block_j == block_i) {
		min = j;
		for (DTidx x = i; x < j; x++)
			if (a[x] < a[min]) min = x;
	}
	else {
		tmp = (block_i +1) * bs - 1; // end of i's block
		min = tmp;
		for (DTidx x = i; x < tmp; x++)  // calculate minimum in i's block
			if (a[x] < a[min]) min = x;
		for (DTidx x = block_j*bs; x <= j; x++) // calculate minimum in j's block
			if (a[x] < a[min]) min = x;
		if (block_j > block_i + 1) { // out-of-block query:
			tmp = c[RMQ_ST->query(block_i+1, block_j-1)]; // index where minimum is
			if (a[tmp] < a[min]) min = tmp;
		}
	}

	return min;
}

/** Divide a into blocks of size log(n)/d. */
RMQ_n_logn::RMQ_n_logn(DT* a, DTidx n, float d) {
	this->a = a;
	this->n = n;
	bs = (DTidx) ceil(log2(n) / d); // calculate block size
	nb = block(n-1)+1;              // number of blocks

	// allocate and fill arrays for out-of-block-queries:
	c = new DTidx[nb];
	mem = sizeof(DTidx) * nb;

	DTidx min;   // position of minimum in current block
	DTidx z=0;   // index in array a
	DTidx end;   // end of current block

	for (DTidx i = 0; i < nb; i++) { // step through blocks
		min = z;              // init minimum
		end = z + bs;         // end of block
		if (end > n) end = n; // last block could be smaller than bs!

		while (++z < end)     // step through current block
			if (a[z] < a[min]) min = z;   // update minimum
		c[i] = min; // store index of minimum
	}

	RMQ_ST = new RMQ_nlogn_1(a, c, nb); // construct sparse table on block-minima
}

/**
 * Standard Constructor. a is the array to be prepared for RMQ.
 * n is the size of the array. Divide a into blocks of size log(n)/4.
 */
RMQ_n_logn::RMQ_n_logn(DT* a, DTidx n) {
	RMQ_n_logn(a, n, 1);
}

/**
 * Destructor. Deletes allocated space.
 */
RMQ_n_logn::~RMQ_n_logn() {
	delete RMQ_ST;
	delete[] c;
}
