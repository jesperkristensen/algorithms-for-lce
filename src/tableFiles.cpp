#include "tableFiles.h"
#include "string.h"
#include "testRandom.h"
#include <stdlib.h>
#include <new>
#include <iostream>
#include <fstream>

void tableFiles(Algorithm** algs, const char** files, const char* output, double preproc_time_limit) {
    uint32 algcount;
    for (algcount = 0; algs[algcount]; algcount++);
    uint32 filecount;
    for (filecount = 0; files[filecount]; filecount++);

    uint32 paircount = 1000000;
    uint32* pairs = new (std::nothrow) uint32[paircount*2];
    if (!pairs) {
        return;
    }

    std::ofstream f(output);

    f << "Files,";
    std::cout <<"\nFiles,";

    for (uint32 alg = 0; algs[alg]; alg++) {
        char algName[ALGORITHM_NAME_SIZE];
        algs[alg]->getName(algName, ALGORITHM_NAME_SIZE);
        f << algName << ",";
        std::cout << algName << ",";
    }
    f << "\n";
    std::cout << "\n";

    for (uint32 file = 0; file < filecount; file++) {
        TestString* s = new (std::nothrow) TestString(files[file]);
        if (!checkStr(s)) {
            f << files[file] << " file too big\n";
            std::cout << files[file] << " file too big\n";
            continue;
        }
        f << files[file] << ",";
        std::cout << files[file] << ",";
        for (uint32 i = 0; i < paircount*2; i += 2) {
            pairs[i] = rand() % s->n;
            pairs[i + 1] = rand() % s->n;
        }
        for (uint32 alg = 0; alg < algcount; alg++) {
            double time = testRandom(s, pairs, paircount, algs[alg], false, preproc_time_limit);
            if (time < 0.0) {
                f << ",";
                std::cout << ",";
            } else {
                f << time << ",";
                std::cout << time << ",";
            }
        }
        f << "\n";
        std::cout << "\n";
        delete s;
    }
    f.close();
    delete[] pairs;
}
