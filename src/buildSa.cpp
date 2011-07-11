#include <limits.h>
#include "qsufsort.h"

void TestString::buildSa() {
    MY_INT *my_sa = new (std::nothrow) MY_INT[n + 1];
    MY_INT *my_sainv = new (std::nothrow) MY_INT[n + 1];
    sa = new (std::nothrow) uint32[n];
    sainv = new (std::nothrow) uint32[n];
    lcp = new (std::nothrow) uint32[n];
    if (!(my_sa && my_sainv && sa && sainv && lcp)) {
        if (my_sa) delete[] my_sa;
        if (my_sainv) delete[] my_sainv;
        if (sa) delete[] sa;
        if (sainv) delete[] sainv;
        if (lcp) delete[] lcp;
        sa = NULL;
        sainv = NULL;
        lcp = NULL;
        return;
    }

    MY_INT k = UCHAR_MAX + 1;
    MY_INT l = 0;

    for (uint32 j = 0; j < n; j++)
        my_sainv[j] = s[j];
    suffixsort(my_sainv, my_sa, MY_INT(n), k, l); // qsufsort.h

    // transform from MY_INT to uint32
    for (uint32 i = 0; i < n; i++) {
        sa[i] = (uint32) my_sa[i + 1];
        sainv[(uint32) my_sa[i + 1]] = i;
    }
    delete[] my_sa;
    delete[] my_sainv;

    // from code_LiviuTinta/LCE/manzini_ds/lcp_aux.c
    // Compute the lcp array from the suffix array
    // using the algorithm by Kasai et al. (CPM '01)

    // rank = sa^{-1}
    // traverse suffixes in rank order
    uint32 h = 0;
    for (uint32 i = 0; i < n; i++) {
        uint32 k = sainv[i];          // rank of s[i ... n-1]
        if (k > 0) {
            uint32 j = sa[k-1];        // predecessor of s[i ... n-1]
            while (i + h < n && j + h < n && s[i + h] == s[j + h])
                h++;
            lcp[k] = h;
        }
        if (h > 0) h--;
    }

    lcp[0] = 0;
}
