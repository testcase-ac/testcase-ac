#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(1, min(10000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> powers;
    for (int p = 1; p <= 8192; p <<= 1) {
        powers.push_back(p);
    }

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int p = rnd.any(powers);
        n = clampN(p + rnd.next(-3, 3));
    } else if (mode == 2) {
        int p = rnd.any(powers);
        n = clampN((p << 1) - rnd.next(0, min(p - 1, 20)));
    } else if (mode == 3) {
        n = rnd.next(21, 500);
    } else if (mode == 4) {
        n = rnd.next(501, 3000);
    } else {
        n = rnd.next(9000, 10000);
    }

    println(n);
    return 0;
}
