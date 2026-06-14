#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int maxGoodEdges(int n) {
    return (n / 2) * ((n + 1) / 2);
}

int clampK(long long k) {
    return int(max(1LL, min(300000LL, k)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int cap = maxGoodEdges(n);
        k = clampK(cap + rnd.next(-2, 2));
    } else if (mode == 2) {
        n = rnd.next(9, 15);
        int cap = maxGoodEdges(n);
        k = rnd.next(1, min(300000, cap));
    } else if (mode == 3) {
        n = rnd.next(16, 100);
        int cap = maxGoodEdges(n);
        k = clampK(cap + rnd.next(-20, 20));
    } else if (mode == 4) {
        vector<int> candidates = {99998, 99999, 100000};
        n = rnd.any(candidates);
        k = rnd.next(1, 300000);
    } else if (mode == 5) {
        n = rnd.next(1000, 100000);
        k = rnd.next(299000, 300000);
    } else if (mode == 6) {
        n = rnd.next(2, 1100);
        int cap = maxGoodEdges(n);
        k = clampK(cap + rnd.next(-1000, 1000));
    } else {
        n = rnd.next(1, 100000);
        k = rnd.next(1, 300000);
    }

    println(n, k);
    return 0;
}
