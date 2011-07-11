#include <stdlib.h>
#include <stdio.h>
#include "graphIncreasingLength.h"
#include "testRandom.h"
#include <new>
#include <iostream>
#include <fstream>

void graphIncreasingLength(Algorithm** algs, enum string_type type, const char* output, double preproc_time_limit, double query_time_limit, uint32 max_n) {
    uint32 paircount = 1000000;
    uint32 algcount;
    for (algcount = 0; algs[algcount]; algcount++);
    bool* ban = new (std::nothrow) bool[algcount];
    double time;
    char algName[ALGORITHM_NAME_SIZE];

    if (!ban)
        return;

    uint32* pairs = new (std::nothrow) uint32[paircount*2];
    if (!pairs) {
        delete[] ban;
        return;
    }

    std::ofstream f(output);

    f << nameStr(type) << " string increasing length,";
    std::cout <<"\n" << nameStr(type) << " string increasing length,";

    for (uint32 alg = 0; algs[alg]; alg++) {
        algs[alg]->getName(algName, ALGORITHM_NAME_SIZE);
        f << algName << ",";
        std::cout << algName << ",";
        ban[alg] = false;
    }
    f << "\n";
    std::cout << "\n";

    for (uint32 n = 2; n <= max_n; n = n<<1) {
        TestString* s = new (std::nothrow) TestString(n, type);
        if (!checkStr(s)) {
            delete[] ban;
            delete[] pairs;
            f.close();
            return;
        }
        for (uint32 i = 0; i < paircount*2; i += 2) {
            pairs[i] = rand() % n;
            pairs[i + 1] = rand() % n;
        }
        f << n << ",";
        std::cout << n << ",";
        for (uint32 alg = 0; algs[alg]; alg++) {
            if (ban[alg]) {
                f << ",";
                std::cout << ",";
            } else {
                time = testRandom(s, pairs, paircount, algs[alg], false, preproc_time_limit);
                if (time < 0.0 || time > query_time_limit) {
                    ban[alg] = true;
                }
                if (time < 0.0) {
                    f << ",";
                    std::cout << ",";
                } else {
                    f << time << ",";
                    std::cout << time << ",";
                }
            }
        }
        f << "\n";
        std::cout << "\n";
        delete s;
    }
    f.close();
    delete[] ban;
    delete[] pairs;
}
