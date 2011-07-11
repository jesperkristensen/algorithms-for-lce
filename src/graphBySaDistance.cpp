#include "graphBySaDistance.h"
#include "timer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

void shuffle_array (std::pair<uint32, uint32>* const a, const uint32 length) {
    for (int32 i = length - 1; i >= 0; i--) {
        const uint32 index = rand() % (i + 1);
        const std::pair<uint32, uint32> tmp = a[index];
        a[index] = a[i];
        a[i] = tmp;
    }
}

void testBySaDistance(TestString* s, Algorithm* a) {
    const uint32 TIMES = 3;

    double start, end;
    bool success = a->preproc(s);
    if (!success)
        return;

    // now compute lce at each step distance
    char algName[ALGORITHM_NAME_SIZE];
    a->getName(algName, ALGORITHM_NAME_SIZE);
    std::cout << algName << ",";

    for (uint32 step = 2; step < s->n; step = step << 1) {

        std::vector< std::pair<uint32, uint32> > all_pairs;
        uint32 i;

        for (i = 0; i + step < s->n; i++) {
            std::pair<uint32, uint32> p;
            p.first = s->sa[i];
            p.second= s->sa[i + step];
            if (p.first > p.second)
                std::swap(p.first, p.second);
            all_pairs.push_back(p);
        }

        double avg = 0;

        for (uint32 k = 0; k < TIMES; k++) {
            shuffle_array(&(all_pairs[0]), all_pairs.size());

            start = gettime();
            for (uint32 j = 0; j < i; j++) {
                a->query(all_pairs[j].first, all_pairs[j].second);
            }
            end = gettime();
            avg += end - start;
        }
        std::cout << avg / TIMES / i << ",";
    }

    a->cleanup();
    std::cout << std::endl;
}

void graphBySaDistance(Algorithm** algs, enum string_type type) {
    TestString* s = new (std::nothrow) TestString(1000, type);
    if (!checkStr(s))
        return;

    std::cout << std::endl << nameStr(type) << " n=1000 string by SA distance,";
    for (uint32 step = 2; step < s->n; step = step << 1) {
        std::cout << step << ",";
    }
    std::cout << std::endl;

    for (uint32 j = 0; algs[j]; j++)
        testBySaDistance(s, algs[j]);
    delete s;
}
