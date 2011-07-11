#include "graphSpaceIncreasingLength.h"
#include <iostream>
#include <fstream>

void graphSpaceIncreasingLength(Algorithm** algs, const char* output, uint32 max_n) {
    std::ofstream f(output);

    f << "Space usage increasing length,";
    std::cout << "\nSpace usage increasing length,";

    for (uint32 alg = 0; algs[alg]; alg++) {
        char algName[ALGORITHM_NAME_SIZE];
        algs[alg]->getName(algName, ALGORITHM_NAME_SIZE);
        f << algName << ",";
        std::cout << algName << ",";
    }
    f << "\n";
    std::cout << "\n";

    for (uint32 i = 2; i <= max_n; i = i<<1) {
        f << i << ",";
        std::cout << i << ",";
        for (uint32 alg = 0; algs[alg]; alg++) {
            f << (double) algs[alg]->spaceUsage(i) << ",";
            std::cout << (double) algs[alg]->spaceUsage(i) << ",";
        }
        f << "\n";
        std::cout << "\n";
    }
    f.close();
}
