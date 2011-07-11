#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "string.h"

# define ALGORITHM_NAME_SIZE 60

class Algorithm {
public:
    /**
     * Preprocess a string for fast LCE-queries.
     *
     * @param s A string
     * @return True iff preprocessing was successful
     */
    virtual bool preproc(TestString*) = 0;

    /**
     * Query some preprocessed string for LCE.
     *
     * @param i The first index of interest in the query
     * @param j The second index of interest in the query
     * @return LCE(i,j) for the string represented by d
     */
    virtual uint32 query(uint32, uint32) = 0;

    /**
     * Free any resources allocated by LCE-preprocessing.
     */
    virtual void cleanup() = 0;
    
    /**
     * A string representing the name of the algorithm.
     *
     * @param name A buffer in which to store the name
     * @param size The size of the buffer in bytes
     */
    virtual void getName(char*, uint32) = 0;

    /**
     * Calculate how much space the preprocessed datastructure would use.
     *
     * @param n Length of the string, not including ending null
     * @return Size of the preprocessed datastructure, in bytes
     */
    virtual uint64 spaceUsage(uint32) = 0;
};

// For used as parameter to an algorithm
typedef uint32 (*IntIntFunc)(uint32);
typedef struct {
    IntIntFunc f;
    const char* name;
} NamedFunc;


#endif
