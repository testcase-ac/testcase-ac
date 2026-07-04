#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 100000;
    int mode = rnd.next(0, 5);
    int n = 1;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int root = rnd.next(1, 316);
        n = root * root;
    } else if (mode == 2) {
        int root = rnd.next(2, 316);
        int square = root * root;
        int delta = rnd.any(vector<int>{-3, -2, -1, 1, 2, 3});
        n = square + delta;
        n = max(1, min(maxN, n));
    } else if (mode == 3) {
        vector<int> candidates;
        for (int scale = 1; scale <= maxN; scale *= 4) {
            for (int b = 0; scale * (8 * b + 7) <= maxN; ++b) {
                candidates.push_back(scale * (8 * b + 7));
            }
        }
        n = rnd.any(candidates);
    } else if (mode == 4) {
        int lo = rnd.next(1, 90000);
        int hi = rnd.next(lo, maxN);
        n = rnd.next(lo, hi);
    } else {
        int root = rnd.next(200, 316);
        int square = root * root;
        n = rnd.next(max(1, square - 500), min(maxN, square + 500));
    }

    println(n);
    return 0;
}
