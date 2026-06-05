#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(long long value) {
    return int(max(1LL, min(10000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> digitBoundaries = {
        1, 2, 8, 9, 10, 11, 98, 99, 100, 101,
        998, 999, 1000, 1001, 9998, 9999, 10000, 10001,
        99998, 99999, 100000, 100001, 999998, 999999,
        1000000, 1000001, 9999998, 9999999, 10000000
    };
    vector<int> usefulK = {
        1, 2, 3, 7, 9, 10, 11, 37, 99, 101, 997,
        1000, 1000000007, 1000000000
    };

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 30);
        k = rnd.next(1, 200);
    } else if (mode == 1) {
        n = rnd.any(digitBoundaries);
        if (rnd.next(0, 1)) {
            n = clampN(n + rnd.next(-2, 2));
        }
        k = rnd.next(1, 100000);
    } else if (mode == 2) {
        n = rnd.next(1, 10000000);
        k = rnd.any(usefulK);
    } else if (mode == 3) {
        n = rnd.next(9990000, 10000000);
        k = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        n = rnd.next(1, 10000);
        k = rnd.next(999900000, 1000000000);
    } else {
        n = rnd.next(1, 10000000);
        k = rnd.next(1, 1000000000);
    }

    println(n, k);
    return 0;
}
