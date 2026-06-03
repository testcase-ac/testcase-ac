#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 99);
        k = rnd.next(1, 99);
    } else if (mode == 1) {
        n = rnd.next(1, 1000000000);
        k = rnd.next(1, 100000);
    } else if (mode == 2) {
        vector<int> powers = {1, 10, 100, 1000, 10000, 100000, 1000000,
                              10000000, 100000000, 1000000000};
        n = rnd.any(powers);
        k = rnd.next(1, 100000);
    } else if (mode == 3) {
        n = rnd.next(1, 1000000000);
        k = rnd.any(vector<int>{2, 4, 5, 8, 10, 16, 20, 25, 40, 50, 80, 100});
    } else if (mode == 4) {
        k = rnd.next(2, 100000);
        int residue = rnd.next(0, k - 1);
        int maxMul = (1000000000 - residue) / k;
        n = residue + k * rnd.next(0, maxMul);
        if (n == 0) n += k;
    } else if (mode == 5) {
        k = rnd.next(1, 100000);
        n = rnd.next(1, min(1000000000, k * rnd.next(1, 10000)));
    } else if (mode == 6) {
        int digits = rnd.next(1, 10);
        int lo = digits == 1 ? 1 : 1;
        for (int i = 1; i < digits; ++i) lo *= 10;
        int hi = digits == 10 ? 1000000000 : lo * 10 - 1;
        n = rnd.next(lo, hi);
        k = rnd.next(max(1, 100000 - rnd.next(0, 999)), 100000);
    } else {
        n = rnd.any(vector<int>{1, 2, 9, 10, 11, 99, 101, 999999937, 1000000000});
        k = rnd.any(vector<int>{1, 2, 3, 7, 9, 11, 37, 99991, 99999, 100000});
    }

    println(n, k);
    return 0;
}
