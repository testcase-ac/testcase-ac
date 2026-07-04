#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

constexpr long long kMinAi = -1000000000LL;
constexpr long long kMaxAi = 1000000000LL;

long long clampValue(long long x) {
    return min(kMaxAi, max(kMinAi, x));
}

vector<long long> makeZeroHeavy(int n) {
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        int pick = rnd.next(0, 9);
        if (pick < 6) {
            a[i] = 0;
        } else {
            a[i] = rnd.next(-5, 5);
        }
    }
    return a;
}

vector<long long> makeProgressionLike(int n) {
    long long start = rnd.next(-20, 20);
    long long step = rnd.next(-6, 6);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = start + step * i + rnd.next(-2, 2);
    }
    return a;
}

vector<long long> makeBalancedBlocks(int n) {
    vector<long long> a;
    while ((int)a.size() < n) {
        int remaining = n - (int)a.size();
        if (remaining >= 2 && rnd.next(0, 3) == 0) {
            long long x = rnd.next(-10, 10);
            a.push_back(x);
            a.push_back(-x);
        } else if (remaining >= 3) {
            long long left = rnd.next(-15, 15);
            long long mid = rnd.next(-15, 15);
            long long right = mid - left;
            a.push_back(left);
            a.push_back(mid);
            a.push_back(right);
        } else {
            a.push_back(rnd.next(-10, 10));
        }
    }
    return a;
}

vector<long long> makeExtremeMix(int n) {
    vector<long long> choices = {
        kMinAi, kMaxAi, -999999999LL, 999999999LL, -1, 0, 1
    };
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 4) == 0) {
            a[i] = rnd.next(-1000, 1000);
        } else {
            a[i] = rnd.any(choices);
        }
    }
    return a;
}

vector<long long> makeRandomSmallRange(int n) {
    long long lo = rnd.next(-30, 5);
    long long hi = rnd.next(5, 30);
    if (rnd.next(0, 3) == 0) {
        lo = rnd.next(-1000000000, -999999950);
        hi = rnd.next(999999950, 1000000000);
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = clampValue(rnd.next(lo, hi));
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    vector<vector<long long>> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 18);
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 2;
        }

        int mode = rnd.next(0, 4);
        if (mode == 0) {
            tests.push_back(makeZeroHeavy(n));
        } else if (mode == 1) {
            tests.push_back(makeProgressionLike(n));
        } else if (mode == 2) {
            tests.push_back(makeBalancedBlocks(n));
        } else if (mode == 3) {
            tests.push_back(makeExtremeMix(n));
        } else {
            tests.push_back(makeRandomSmallRange(n));
        }
    }

    println((int)tests.size());
    for (const auto& test : tests) {
        println((int)test.size());
        println(test);
    }

    return 0;
}
