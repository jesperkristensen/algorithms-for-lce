/*
 Written by: Liviu Tinta
 Purpose: to access function suffixsort from the qsufsort.a library
*/

#ifndef _QSUFSORT_H_
#define _QSUFSORT_H_

#ifdef __cplusplus
extern "C" {
#endif

// Modified on April 26, 2009 by Liviu Tinta

// Original Jesper Larsson values
//typedef int MY_INT;
//#define MY_INT_MAX INT_MAX 

#include "types.h" // includes <stdint.h>
typedef intptr_t MY_INT;
#define MY_INT_MAX INTPTR_MAX

// End modification

/* Makes suffix array p of x. x becomes inverse of p. p and x are both of size
   n+1. Contents of x[0...n-1] are integers in the range l...k-1. Original
   contents of x[n] is disregarded, the n-th symbol being regarded as
   end-of-string smaller than all other symbols.*/

void suffixsort(MY_INT *x, MY_INT *p, MY_INT n, MY_INT k, MY_INT l);

#ifdef  __cplusplus
}
#endif

#endif
