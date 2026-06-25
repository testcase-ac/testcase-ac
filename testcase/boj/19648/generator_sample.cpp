#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1000000000;

int nearValue(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(MAX_N, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 100);
    } else if (mode == 2) {
        n = rnd.next(101, 10000);
    } else if (mode == 3) {
        n = rnd.next(10001, 1000000);
    } else if (mode == 4) {
        n = rnd.next(1000001, MAX_N);
    } else if (mode == 5) {
        vector<int> powers = {16, 32, 64, 128, 256, 512, 1024,
                              4096, 65536, 1048576, 536870912};
        n = nearValue(rnd.any(powers), rnd.next(0, 5));
    } else if (mode == 6) {
        vector<int> edges = {1, 2, 3, 999999937, 999999999, MAX_N};
        n = nearValue(rnd.any(edges), rnd.next(0, 3));
    } else {
        n = MAX_N - rnd.next(0, 1000);
    }

    println(n);
    return 0;
}
