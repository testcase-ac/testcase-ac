#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000000000LL;

    vector<long long> powers;
    for (long long x = 1; x <= MAX_VALUE; x *= 10) {
        powers.push_back(x);
        if (x == MAX_VALUE) break;
    }

    int t = rnd.next(1, 100);
    vector<pair<long long, long long>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 6);
        long long a = 0;
        long long b = 0;

        if (mode == 0) {
            b = rnd.next(0LL, MAX_VALUE);
            a = b;
        } else if (mode == 1) {
            a = rnd.next(0LL, 100000LL);
            b = min(MAX_VALUE, a + rnd.next(0LL, 200LL));
        } else if (mode == 2) {
            long long p = rnd.any(powers);
            long long span = rnd.next(0LL, 30LL);
            a = max(0LL, p - span);
            b = min(MAX_VALUE, p + rnd.next(0LL, 30LL));
        } else if (mode == 3) {
            long long p = rnd.any(powers);
            long long edge = p - 1;
            long long left = rnd.next(0LL, min(edge, 50LL));
            long long right = rnd.next(0LL, min(MAX_VALUE - edge, 50LL));
            a = edge - left;
            b = edge + right;
        } else if (mode == 4) {
            long long hi = rnd.next(0LL, MAX_VALUE);
            long long width = rnd.next(0LL, 1000000LL);
            a = hi > width ? hi - width : 0;
            b = hi;
        } else if (mode == 5) {
            long long width = rnd.next(0LL, 1000000LL);
            a = MAX_VALUE - width;
            b = MAX_VALUE;
        } else {
            a = rnd.next(0LL, MAX_VALUE);
            b = rnd.next(a, MAX_VALUE);
        }

        cases.push_back({a, b});
    }

    println(t);
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }

    return 0;
}
