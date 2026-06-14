#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int randomValue(int mode) {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 499979, 499993
    };
    static const vector<int> primePowers = {
        4, 8, 9, 16, 25, 27, 32, 49, 81, 121, 169, 512, 1024, 59049, 262144
    };
    static const vector<int> composites = {
        6, 10, 12, 18, 30, 42, 60, 84, 90, 120, 180, 210, 2310, 30030
    };

    if (mode == 0) return rnd.any(primes);
    if (mode == 1) return rnd.any(primePowers);
    if (mode == 2) return rnd.any(composites);
    if (mode == 3) return rnd.next(2, 80);
    return rnd.next(2, 500000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 35 : 18);
    int maxPlans = min(60, n * (n + 1) / 2);
    int m = rnd.next(0, maxPlans);
    if (mode == 0) m = 0;
    if (mode == 1) m = rnd.next(1, min(12, maxPlans));

    vector<int> a(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        int localMode = rnd.next() < 0.35 ? rnd.next(0, 4) : valueMode;
        a[i] = randomValue(localMode);
    }

    vector<pair<int, int>> ranges;
    if (mode == 1) {
        for (int k = 0; k < m; ++k) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            ranges.push_back({l, r});
        }
    } else if (mode == 2) {
        for (int k = 0; k < m; ++k) {
            int center = rnd.next(1, n);
            int radius = rnd.next(0, min(4, max(center - 1, n - center)));
            int l = max(1, center - radius);
            int r = min(n, center + radius);
            ranges.push_back({l, r});
        }
    } else if (mode == 3) {
        for (int k = 0; k < m; ++k) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, min(n, l + rnd.next(0, 3)));
            ranges.push_back({l, r});
        }
    } else {
        vector<pair<int, int>> allRanges;
        for (int l = 1; l <= n; ++l)
            for (int r = l; r <= n; ++r)
                allRanges.push_back({l, r});
        shuffle(allRanges.begin(), allRanges.end());
        ranges.assign(allRanges.begin(), allRanges.begin() + m);
    }

    println(n, static_cast<int>(ranges.size()));
    println(a);
    for (auto range : ranges) {
        println(range.first, range.second);
    }
}
