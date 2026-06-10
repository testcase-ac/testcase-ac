#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

const long long MAX_AB = 1000000000LL;
const long long MAX_X = 2000000000LL;

long long boundedProduct(long long a, long long b, long long limit) {
    if (a > limit / b) return limit;
    return a * b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    vector<vector<long long>> tests;

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 6);
        long long a, b, x;

        if (mode == 0) {
            a = rnd.next(1LL, 30LL);
            b = rnd.next(1LL, 30LL);
            x = rnd.next(1LL, 120LL);
        } else if (mode == 1) {
            long long g = rnd.next(1LL, 1000LL);
            a = boundedProduct(g, rnd.next(1LL, 2000LL), MAX_AB);
            b = boundedProduct(g, rnd.next(1LL, 2000LL), MAX_AB);
            x = boundedProduct(g, rnd.next(1LL, 4000LL), MAX_X);
        } else if (mode == 2) {
            long long g = rnd.next(1LL, 1000000LL);
            a = g;
            b = boundedProduct(g, rnd.next(1LL, 1000LL), MAX_AB);
            if (rnd.next(0, 1)) swap(a, b);
            x = rnd.next(1LL, MAX_X);
        } else if (mode == 3) {
            long long v = rnd.next(1LL, MAX_AB);
            a = v;
            b = v;
            x = rnd.next(1LL, MAX_X);
        } else if (mode == 4) {
            a = rnd.next(MAX_AB - 2000, MAX_AB);
            b = rnd.next(MAX_AB - 2000, MAX_AB);
            x = rnd.next(MAX_X - 4000, MAX_X);
        } else {
            a = rnd.next(1LL, MAX_AB);
            b = rnd.next(1LL, MAX_AB);
            x = rnd.next(1LL, MAX_X);
        }

        tests.push_back({a, b, x});
    }

    shuffle(tests.begin(), tests.end());
    println((int)tests.size());
    for (const auto& test : tests) {
        println(test[0], test[1], test[2]);
    }

    return 0;
}
