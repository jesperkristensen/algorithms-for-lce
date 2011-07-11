#include <stdlib.h>
#include <stdio.h>
#include "graphValue.h"
#include <new>
#include <iostream>
#include <fstream>
#include "timer.h"
#include <vector>

void sort(double* array, uint32 length) {
    for (uint32 i = 0; i < length; i++) {
        uint32 min = i;
        for (uint32 j = i + 1; j < length; j++) {
            if (array[j] > array[min])
                min = j;
        }
        double temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
}

void graphValue(Algorithm** algs, enum string_type type, uint32 n, const char* output, uint32 repeats) {
    uint32 count = 100000000;

    uint32 algcount;
    for (algcount = 0; algs[algcount]; algcount++);

    double* valueSum = new (std::nothrow) double[algcount*(n+1)];
    if (!valueSum)
        return;

    std::ofstream f(output);

    f << nameStr(type) << " string length " << n << " by LCE value,";
    std::cout <<"\n" << nameStr(type) << " string length " << n << " by LCE value,";

    TestString* s = new (std::nothrow) TestString(n, type);
    if (!checkStr(s)) {
        delete[] valueSum;
        f.close();
        return;
    }

    bool success = algs[0]->preproc(s);
    if (!success) {
        delete s;
        delete[] valueSum;
        f.close();
        return;
    }
    // forall (i,j): (i,j) isin all_pairs[v] => LCE(i,j) = v
    std::vector< std::pair<uint32, uint32> >* all_pairs = new (std::nothrow) std::vector< std::pair<uint32, uint32> >[n+1];
    if (!all_pairs) {
        algs[0]->cleanup();
        delete s;
        delete[] valueSum;
        f.close();
        return;
    }
    for (uint32 i = 0; i < count; i++) {
        std::pair<uint32, uint32> p;
        p.first = rand() % n;
        p.second = rand() % n;
        uint32 v = algs[0]->query(p.first, p.second);
        if (all_pairs[v].size() < repeats)
            all_pairs[v].push_back(p);
    }
    algs[0]->cleanup();

    for (uint32 alg = 0; algs[alg]; alg++) {
        Algorithm* a = algs[alg];
        char algName[ALGORITHM_NAME_SIZE];
        a->getName(algName, ALGORITHM_NAME_SIZE);
        f << algName << ",";
        std::cout << algName << ",";

        bool success = a->preproc(s);
        if (!success) {
            continue;
        }
        for (uint32 val = 0; val <= n; val++) {
            if (all_pairs[val].size() >= repeats) {
                double time[3];
                for (uint32 x = 0; x < 3; x++) {
                    double start = gettime();
                    for (uint32 i = 0; i < repeats; i++) {
                        a->query(all_pairs[val][i].first, all_pairs[val][i].second);
                    }
                    double end = gettime();
                    time[x] = end - start;
                }
                sort(time, 3);
                valueSum[alg+algcount*val] = time[1];
            } else {
                valueSum[alg+algcount*val] = 0.0;
            }
        }
        a->cleanup();
    }

    f << "\n";
    std::cout << "\n";

    for (uint32 lce = 0; lce <= n; lce++) {
        f << lce << ",";
        for (uint32 alg = 0; algs[alg]; alg++) {
            if (valueSum[alg+algcount*lce] > 0)
                f << (valueSum[alg+algcount*lce] / repeats) << ",";
            else
                f << ",";
        }
        f << "\n";
    }

    delete s;
    f.close();
    delete[] valueSum;
}
