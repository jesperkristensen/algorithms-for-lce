#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "algorithm.h"

#include "algDirectComp.h"
#include "algDirectLookup.h"
#include "algDirectCompLookup.h"
#include "algHash.h"
#include "algHash2Ldq.h"
#include "algHash2LCache.h"
#include "algHash2LCacheMul.h"
#include "algHash3L.h"
#include "algHash3Ld.h"
#include "algHash3Ldq.h"
#include "algHashLog.h"
#include "algHashLogD.h"
#include "algHashLogDCache.h"
#include "algRmqN.h"
#include "algRmq1.h"
#include "algRmq11.h"
#ifndef _MSC_VER
#include "algRmq.h"
#endif

#include "correctness.h"
#include "functionalTest.h"
#include "graphIncreasingLength.h"
#include "graphSpaceIncreasingLength.h"
#include "graphValue.h"
#include "tableFiles.h"
#include "graphBySaDistance.h"
#include "cacheTest.h"
#include "plotDirectCompLookup.h"

#ifdef _MSC_VER
double log2(double n) {
    return log(n) / log(2.0);  
}
#endif

uint32 const1f(uint32 _) { return 1; } NamedFunc const1 = {const1f, "1"};
uint32 const10f(uint32 _) { return 10; } NamedFunc const10 = {const10f, "10"};
uint32 const20f(uint32 _) { return 20; } NamedFunc const20 = {const20f, "20"};
uint32 const100f(uint32 _) { return 100; } NamedFunc const100 = {const100f, "100"};
uint32 sqrt_nf(uint32 n) { return (uint32) sqrt((double)n); } NamedFunc sqrt_n = {sqrt_nf, "sqrt n"};
uint32 sqrt_n_d2f(uint32 n) { return (uint32) (.5*sqrt((double)n)); } NamedFunc sqrt_n_d2 = {sqrt_n_d2f, "1/2sqrt n"};
uint32 sqrt_n_d4f(uint32 n) { return (uint32) (.25*sqrt((double)n)); } NamedFunc sqrt_n_d4 = {sqrt_n_d4f, "1/4sqrt n"};
uint32 sqrt_n_2f(uint32 n) { return (uint32) (2*sqrt((double)n)); } NamedFunc sqrt_n_2 = {sqrt_n_2f, "2sqrt n"};
uint32 sqrt_n_4f(uint32 n) { return (uint32) (4*sqrt((double)n)); } NamedFunc sqrt_n_4 = {sqrt_n_4f, "4sqrt n"};
uint32 sqrt_n_8f(uint32 n) { return (uint32) (8*sqrt((double)n)); } NamedFunc sqrt_n_8 = {sqrt_n_8f, "8sqrt n"};
uint32 sqrt_n_16f(uint32 n) { return (uint32) (16*sqrt((double)n)); } NamedFunc sqrt_n_16 = {sqrt_n_16f, "16sqrt n"};
uint32 pow23f(uint32 n) { return (uint32) pow(n, 2./3.); } NamedFunc pow23 = {pow23f, "n^{2/3}"};
uint32 pow13f(uint32 n) { return (uint32) pow(n, 1./3.); } NamedFunc pow13 = {pow13f, "n^{1/3}"};
uint32 log2_nf(uint32 n) { return (uint32) log2((double)n); } NamedFunc log2_n = {log2_nf, "log n"};
uint32 ndlog2nf(uint32 n) { return (uint32) (((double)n)/log2((double)n)); } NamedFunc ndlog2n = {ndlog2nf, "n/log n"};

int main(int argc, char* argv[]) {
#if defined(CACHE_ALLA)
    cacheTest(2000000, ALL_A_STRING);
#elif defined(CACHE_RAND10)
    cacheTest(2000000, RANDOM10_STRING);
#else
    Algorithm* algs[] = {
        new AlgorithmDirectComp,
        new AlgorithmDirectLookup,
        new AlgorithmDirectCompLookup(&log2_n),
        new AlgorithmDirectCompLookup(&sqrt_n),
        //new AlgorithmDirectCompLookup(&sqrt_n_2),
        new AlgorithmDirectCompLookup(&ndlog2n),
        // 2 = 2 levels, 3 = 3 levels, L = log n levels
        // A = average case, W = worst case
        // Q = quick, P = parameter
        new Fingerprint2W(&sqrt_n),
        //new Fingerprint2AQ(&const20),
        //new Fingerprint2W(&const100),
        new Fingerprint2AQ(&sqrt_n_d4),
        new Fingerprint2AQ(&sqrt_n_d2),
        new Fingerprint2AQ(&sqrt_n),
        new Fingerprint2AQ(&sqrt_n_2),
        new Fingerprint2AQ(&sqrt_n_4),
        new Fingerprint2AQ(&sqrt_n_8),
        new Fingerprint2AQ(&sqrt_n_16),
        //new Fingerprint2AQ(&ln_n),
        new Fingerprint2AQCacheHorizShift(&sqrt_n),
        new Fingerprint2AQCacheHorizMult(&sqrt_n),
        new Fingerprint3W(&pow23, &pow13),
        new Fingerprint3AP(&pow13, &pow23, &pow23, &pow13),
        new Fingerprint3AP(&const1, &const1, &pow23, &pow13),
        new Fingerprint3AQ(&pow23, &pow13),
        new FingerprintLW(),
        new FingerprintLA(),
        new FingerprintLACacheVertiMult(),
        new AlgorithmRmqN,
        new AlgorithmRmq1,
        new AlgorithmRmq11,
#ifndef _MSC_VER
        new AlgorithmRmq(RMQ_1_N),
        new AlgorithmRmq(RMQ_N_1),
        new AlgorithmRmq(RMQ_N_LOGN_2),
        new AlgorithmRmq(RMQ_N_LOGN_4),
        //new AlgorithmRmq(RMQ_SUCCINCT), //destructor crash
        //new AlgorithmRmq(RMQ_N_LOGN_D2),
        //new AlgorithmRmq(RMQ_N_LOGN_D4),
        //new AlgorithmRmq(RMQ_OPTIMAL),
#endif
        NULL
    };

    correctness(algs, RANDOM10_STRING);
    correctness(algs, ALL_A_STRING);
    correctness(algs, REPEAT_POW_STRING);

    double preproc_limit = 6;
    double query_limit = 1e-6;
    uint32 max_n = 10000000;

    //functionalTest(algs);
    graphIncreasingLength(algs, RANDOM10_STRING, "results/length-rand10.txt", preproc_limit, query_limit, max_n);
    graphIncreasingLength(algs, ALL_A_STRING, "results/length-alla.txt", preproc_limit, 1e-5, max_n);
    graphIncreasingLength(algs, REPEAT_POW_STRING, "results/length-repeat-pow.txt", preproc_limit, 1e-5, max_n);
    graphSpaceIncreasingLength(algs, "results/space.txt", max_n);
    //graphBySaDistance(algs, RANDOM10_STRING);
    //graphBySaDistance(algs, ALL_A_STRING);
    //graphIncreasingLength(algs, RANDOM4_STRING, "results/length-rand4.txt", preproc_limit, query_limit, max_n);
    //graphIncreasingLength(algs, RANDOM255_STRING, "results/length-rand255.txt", preproc_limit, query_limit, max_n);
    graphValue(algs, RANDOM4_STRING, 1000, "results/value-rand4.txt", 1000);
    graphValue(algs, RANDOM10_REPEAT10_STRING, 1000, "results/value-repeat10-10.txt", 1000);
    graphValue(algs, ALL_A_STRING, 1000, "results/value-alla.txt", 10000);

    Algorithm* filealgs[] = {
        new AlgorithmDirectComp,
        new Fingerprint2AQ(&sqrt_n),
        new Fingerprint3AQ(&pow23, &pow13),
        new FingerprintLA(),
        new AlgorithmRmq1,
        NULL
    };
    const char* files[] = {
        "tests/test.txt",
        "tests/canterbury/book1",
        "tests/canterbury/kennedy.xls",
        "tests/canterbury/E.coli",
        "tests/canterbury/bible.txt",
        "tests/canterbury/world192.txt",
        NULL
    };
    tableFiles(filealgs, files, "results/files.txt", 1000);
    
    //plotDirectCompLookup(ALL_A_STRING, "results/complookup-alla.txt", 10000, 499, preproc_limit);
    /*
    Algorithm* cacheAlgs[] = {
        new Fingerprint2AQ(&sqrt_n),
        new Fingerprint2AQCacheHorizShift(&sqrt_n),
        new Fingerprint2AQCacheHorizMult(&sqrt_n),
        NULL
    };
    graphIncreasingLength(cacheAlgs, RANDOM2_STRING, "results/length-rand2.txt", preproc_limit, query_limit, max_n);
    */
#endif
    printf("\nThe end\n");
}
