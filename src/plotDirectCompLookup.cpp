#include "plotDirectCompLookup.h"
#include "algorithm.h"
#include "algDirectCompLookup.h"
#include "testRandom.h"
#include <new>
#include <stdlib.h>
#include <iostream>
#include <fstream>

uint32 idf(uint32 p) { return p; } NamedFunc id = {idf, "id"};

void plotDirectCompLookup(enum string_type type, const char* output, uint32 n, uint32 t_step, uint32 preproc_time_limit) {
    uint32 paircount = 1000000;
    uint32* pairs = new (std::nothrow) uint32[paircount*2];
    if (!pairs) {
        return;
    }

    std::ofstream f(output);

    f << "DirectCompLookup tests,DirectCompLookup<t>,\n";
    std::cout <<"\nDirectCompLookup tests,DirectCompLookup<t>,\n";

    for (uint32 i = 0; i < paircount*2; i += 2) {
        pairs[i] = rand() % n;
        pairs[i + 1] = rand() % n;
    }
    for (uint32 t = 1; t <= n; t += t_step) {
        TestString* s = new (std::nothrow) TestString(n, type);
        if (!checkStr(s)) {
            delete[] pairs;
            f.close();
            return;
        }
        AlgorithmDirectCompLookup alg(&id, t);
        double time = testRandom(s, pairs, paircount, &alg, false, preproc_time_limit);
        f << t << "," << time << ",\n";
        std::cout << t << "," << time << ",\n";
        delete s;
    }
    f.close();
}
