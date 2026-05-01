#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter 1: choose N in small, medium, or large range
    int sizeType = rnd.next(0, 2);
    int N;
    if (sizeType == 0) {
        // small
        N = rnd.next(1, 3);
    } else if (sizeType == 1) {
        // medium
        N = rnd.next(4, 6);
    } else {
        // large but still hand-checkable
        N = rnd.next(7, 9);
    }

    // Hyper-parameter 2: choose cost range type
    int rangeType = rnd.next(0, 2);
    int costMax;
    if (rangeType == 0) {
        // full range
        costMax = 10000;
    } else if (rangeType == 1) {
        // small costs
        costMax = 100;
    } else {
        // moderate costs
        costMax = 1000;
    }

    // Hyper-parameter 3: pattern type (uniform or diagonal-favored)
    int pattern = rnd.next(0, 1);

    // Output N
    println(N);

    // Generate cost matrix
    for (int i = 0; i < N; i++) {
        vector<int> row;
        for (int j = 0; j < N; j++) {
            int c;
            if (pattern == 1 && i == j) {
                // diagonal entries are small
                int hi = min(costMax, 10);
                c = rnd.next(1, hi);
            } else if (pattern == 1) {
                // off-diagonal entries are larger
                int lo = costMax / 2 + 1;
                c = rnd.next(lo, costMax);
            } else {
                // uniform random
                c = rnd.next(1, costMax);
            }
            row.push_back(c);
        }
        println(row);
    }

    return 0;
}
