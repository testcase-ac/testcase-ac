#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(10, min(1000000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        10, 11, 12, 13, 19, 20,
        97, 100, 101, 103,
        997, 1000, 1009,
        99991, 100000, 100003,
        999983, 1000000
    };
    vector<int> powers = {10, 100, 1000, 10000, 100000, 1000000};

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(10, 200);
    } else if (mode == 1) {
        int base = rnd.any(powers);
        n = clampN(base + rnd.next(-25, 25));
    } else if (mode == 2) {
        n = rnd.any(anchors);
    } else if (mode == 3) {
        n = rnd.next(900000, 1000000);
    } else if (mode == 4) {
        n = rnd.next(10, 1000000);
    } else {
        int digits = rnd.next(2, 6);
        n = 0;
        for (int i = 0; i < digits; ++i) {
            n = n * 10 + rnd.any(vector<int>{0, 1, 7, 9});
        }
        n = clampN(n);
    }

    println(n);
    return 0;
}
