#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long clampValue(long long x) {
    return max(0LL, min(4000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> anchors = {
        0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL,
        10LL, 20LL, 100LL, 99991LL, 1000000000LL,
        3999999900LL, 3999999990LL, 4000000000LL
    };

    int mode = rnd.next(0, 5);
    int t = mode == 0 ? 0 : rnd.next(1, 20);
    vector<long long> values;
    values.reserve(t);

    for (int i = 0; i < t; ++i) {
        int kind = rnd.next(0, 5);
        long long n = 0;
        if (kind == 0) {
            n = rnd.next(0LL, 20LL);
        } else if (kind == 1) {
            long long base = rnd.any(anchors);
            n = clampValue(base + rnd.next(-10LL, 10LL));
        } else if (kind == 2) {
            n = rnd.next(10LL, 100000LL);
        } else if (kind == 3) {
            n = rnd.next(999900000LL, 1000100000LL);
        } else if (kind == 4) {
            n = rnd.next(3999900000LL, 4000000000LL);
        } else {
            long long block = rnd.next(0LL, 4000LL) * 1000000LL;
            n = clampValue(block + rnd.next(0LL, 999999LL));
        }
        values.push_back(n);
    }

    println(t);
    for (long long n : values) {
        println(n);
    }

    return 0;
}
