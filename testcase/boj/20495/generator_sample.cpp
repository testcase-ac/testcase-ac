#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<pair<long long, long long>> ranges;

    if (mode == 0) {
        long long start = rnd.next(-1000000, 1000000);
        long long gap = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            long long b = rnd.next(0, 20);
            long long a = start + i * gap;
            ranges.push_back({a, b});
        }
    } else if (mode == 1) {
        long long center = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            long long a = center + rnd.next(-30, 30);
            long long b = rnd.next(20, 120);
            ranges.push_back({a, b});
        }
    } else if (mode == 2) {
        int groups = rnd.next(1, min(5, n));
        vector<pair<long long, long long>> base;
        for (int i = 0; i < groups; ++i) {
            long long a = rnd.next(-200, 200);
            long long b = rnd.next(0, 80);
            base.push_back({a, b});
        }
        for (int i = 0; i < n; ++i) {
            ranges.push_back(rnd.any(base));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(-1000, 1000);
            long long b = rnd.next(0, 3) == 0 ? rnd.next(1, 50) : 0;
            ranges.push_back({a, b});
        }
    } else if (mode == 4) {
        long long center = rnd.next(-500, 500);
        for (int i = 0; i < n; ++i) {
            long long a = center + rnd.next(-5, 5);
            long long b = rnd.next(i, i + 100);
            ranges.push_back({a, b});
        }
    } else {
        ranges.push_back({-1000000000LL, 0});
        ranges.push_back({1000000000LL, 0});
        while ((int)ranges.size() < n) {
            long long a = rnd.next(-1000000000, 1000000000);
            long long maxB = min(1000000000LL, 1000000000LL - llabs(a));
            if (rnd.next(0, 2) == 0) maxB = 1000000000LL;
            long long b = rnd.next(0LL, maxB);
            ranges.push_back({a, b});
        }
    }

    shuffle(ranges.begin(), ranges.end());

    println(n);
    for (auto [a, b] : ranges) {
        println(a, b);
    }

    return 0;
}
