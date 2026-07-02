#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

long long triangular(long long n) {
    return n * (n + 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxK = 1000000000;
    int mode = rnd.next(0, 5);
    long long k = 0;

    if (mode == 0) {
        k = rnd.next(0, 50);
    } else if (mode == 1) {
        k = rnd.next(0, 500);
    } else if (mode == 2) {
        long long n = rnd.next(0, 44720);
        long long base = min<long long>(maxK, triangular(n));
        long long delta = rnd.next(-3, 3);
        k = max(0LL, min<long long>(maxK, base + delta));
    } else if (mode == 3) {
        vector<int> anchors = {0, 1, 2, 3, 4, 49, 50, 51, 499, 500, 501, maxK};
        k = rnd.any(anchors);
    } else if (mode == 4) {
        k = maxK - rnd.wnext(100000, 3);
    } else {
        k = rnd.next(0, maxK);
    }

    println(k);
    return 0;
}
