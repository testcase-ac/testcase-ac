#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 1000000000;
    vector<int> candidates = {
        1, 2, 3, 4, 5, 6, 9, 10, 12, 16, 25, 36,
        999983, 1000000, 999950884, limit
    };

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 200);
    } else if (mode == 1) {
        int side = rnd.next(1, 31623);
        n = side * side;
    } else if (mode == 2) {
        int a = rnd.next(1, 100000);
        int b = rnd.next(1, 100000);
        n = min(1LL * a * b, 1LL * limit);
    } else if (mode == 3) {
        int base = rnd.next(1, 31623);
        n = min(1LL * base * (base + rnd.next(0, 20)), 1LL * limit);
    } else if (mode == 4) {
        n = limit - rnd.next(0, 100000);
    } else {
        n = rnd.any(candidates);
    }

    println(n);
    return 0;
}
