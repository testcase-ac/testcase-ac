#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a case to diversify
    int caseType = rnd.next(1, 5);
    long long N = 1;

    if (caseType == 1) {
        // Small N
        N = rnd.next(1, 15);
    } else if (caseType == 2) {
        // Large random N
        N = rnd.next(100000000, 1000000000);
    } else if (caseType == 3) {
        // Power of two
        int k = rnd.next(0, 29);
        N = 1LL << k;
        if (N < 1) N = 1;
    } else if (caseType == 4) {
        // All ones in binary of length k
        int k = rnd.next(1, 29);
        N = (1LL << k) - 1;
    } else {
        // Random with about half bits = 1
        int k = rnd.next(1, 29);
        // Determine popcount in [k/4, 3k/4]
        int lo = max(1, k / 4);
        int hi = max(1, (3 * k) / 4);
        int pop = rnd.next(lo, hi);
        vector<int> bits(k, 0);
        // Ensure highest bit is 1
        bits[k-1] = 1;
        int remOnes = pop - 1;
        vector<int> idxs;
        for (int i = 0; i < k-1; ++i) idxs.push_back(i);
        shuffle(idxs.begin(), idxs.end());
        for (int i = 0; i < remOnes && i < (int)idxs.size(); ++i) {
            bits[idxs[i]] = 1;
        }
        N = 0;
        for (int i = 0; i < k; ++i) {
            if (bits[i]) N |= (1LL << i);
        }
    }

    // Guarantee constraints
    if (N < 1) N = 1;
    if (N > 1000000000) N = 1000000000;

    // Output N
    println(N);
    return 0;
}
