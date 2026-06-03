#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

int pickCoprime(int a, int lo, int hi) {
    for (int tries = 0; tries < 100; ++tries) {
        int b = rnd.next(lo, hi);
        if (gcd(a, b) == 1) return b;
    }
    for (int b = lo; b <= hi; ++b) {
        if (gcd(a, b) == 1) return b;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    vector<tuple<int, int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int a, b, d;

        if (mode == 0) {
            a = b = rnd.next(1, 30);
            d = rnd.next(1, a);
        } else if (mode == 1) {
            a = rnd.next(2, 60);
            b = pickCoprime(a, 1, 60);
            d = rnd.next(1, max(a, b));
        } else if (mode == 2) {
            int g = rnd.next(2, 20);
            int x = rnd.next(1, 25);
            int y = rnd.next(1, 25);
            a = g * x;
            b = g * y;
            d = g * rnd.next(1, max(x, y));
        } else if (mode == 3) {
            int g = rnd.next(2, 20);
            int x = rnd.next(1, 25);
            int y = rnd.next(1, 25);
            a = g * x;
            b = g * y;
            d = rnd.next(1, max(a, b));
            if (d % g == 0) {
                d = d == max(a, b) ? d - 1 : d + 1;
                if (d < 1) d = 1;
            }
        } else if (mode == 4) {
            a = 10000000;
            b = rnd.next(9999900, 10000000);
            d = rnd.next(9999900, 10000000);
        } else {
            a = rnd.next(1, 100);
            b = rnd.next(1, 100);
            d = rnd.next(1, max(a, b));
        }

        cases.emplace_back(a, b, d);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [a, b, d] : cases) {
        println(a, b, d);
    }

    return 0;
}
