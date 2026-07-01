#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedProduct(const vector<int>& factors, int limit) {
    long long value = 1;
    for (int factor : factors) {
        if (value * factor > limit) break;
        value *= factor;
    }
    return static_cast<int>(value);
}

int randomSquareRich(int limit) {
    vector<int> factors;
    vector<int> primeChoices = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int primeCount = rnd.next(1, 4);

    for (int i = 0; i < primeCount; ++i) {
        int p = rnd.any(primeChoices);
        int exponent = rnd.next(0, 4);
        for (int j = 0; j < exponent; ++j) factors.push_back(p);
    }

    shuffle(factors.begin(), factors.end());
    return max(1, boundedProduct(factors, limit));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int a = 1;
        int b = 1;

        if (mode == 0) {
            a = rnd.next(1, 100);
            b = rnd.next(1, 100);
        } else if (mode == 1) {
            int g = rnd.next(1, 10000);
            a = g * rnd.next(1, 100);
            b = g * rnd.next(1, 100);
        } else if (mode == 2) {
            a = randomSquareRich(1000000000);
            b = randomSquareRich(1000000000);
        } else if (mode == 3) {
            int g = randomSquareRich(100000);
            int x = randomSquareRich(10000);
            int y = randomSquareRich(10000);
            a = boundedProduct({g, x}, 1000000000);
            b = boundedProduct({g, y}, 1000000000);
        } else if (mode == 4) {
            a = rnd.any(vector<int>{1, 2, 99991, 999983, 1000000000});
            b = rnd.next(1, 1000000000);
        } else {
            a = rnd.next(1, 1000000000);
            b = rnd.next(1, 1000000000);
        }

        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }

    return 0;
}
