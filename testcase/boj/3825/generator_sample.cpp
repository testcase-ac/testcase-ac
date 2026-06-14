#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int norm2(pair<int, int> p) {
    return p.first * p.first + p.second * p.second;
}

bool isRepresentableNorm(int x) {
    for (int a = 0; a * a <= x; ++a) {
        for (int b = 0; a * a + b * b <= x; ++b) {
            if (a * a + b * b == x && x > 1) {
                return true;
            }
        }
    }
    return false;
}

bool hasGaussianFactorNorm(int x, const vector<int>& representable) {
    for (int d : representable) {
        if (d > 1 && d < x && x % d == 0) {
            return true;
        }
    }
    return false;
}

pair<int, int> randomFrom(const vector<pair<int, int>>& values) {
    return values[rnd.next(static_cast<int>(values.size()))];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> all;
    vector<pair<int, int>> axes;
    vector<pair<int, int>> tiny;
    vector<pair<int, int>> nearLimit;
    vector<pair<int, int>> likelyPrime;
    vector<pair<int, int>> likelyComposite;
    vector<int> representable;

    for (int x = 2; x < 20000; ++x) {
        if (isRepresentableNorm(x)) {
            representable.push_back(x);
        }
    }

    for (int m = -141; m <= 141; ++m) {
        for (int n = -141; n <= 141; ++n) {
            int q = m * m + n * n;
            if (q <= 1 || q >= 20000) {
                continue;
            }

            pair<int, int> p = {m, n};
            all.push_back(p);
            if (m == 0 || n == 0) {
                axes.push_back(p);
            }
            if (q <= 50) {
                tiny.push_back(p);
            }
            if (q >= 18000) {
                nearLimit.push_back(p);
            }
            if (hasGaussianFactorNorm(q, representable)) {
                likelyComposite.push_back(p);
            } else {
                likelyPrime.push_back(p);
            }
        }
    }

    int t = rnd.next(20, 80);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(100);
        pair<int, int> p;
        if (mode < 18) {
            p = randomFrom(tiny);
        } else if (mode < 35) {
            p = randomFrom(axes);
        } else if (mode < 55) {
            p = randomFrom(nearLimit);
        } else if (mode < 75) {
            p = randomFrom(likelyPrime);
        } else if (mode < 95) {
            p = randomFrom(likelyComposite);
        } else {
            p = randomFrom(all);
        }

        if (rnd.next(2)) {
            swap(p.first, p.second);
        }
        if (rnd.next(2)) {
            p.first = -p.first;
        }
        if (rnd.next(2)) {
            p.second = -p.second;
        }

        println(p.first, p.second);
    }

    return 0;
}
