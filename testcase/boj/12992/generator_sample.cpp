#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    int k = rnd.next(1, n);
    vector<pair<long long, long long>> intervals;

    if (mode == 0) {
        long long center = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            long long leftPad = rnd.next(0, 30);
            long long rightPad = rnd.next(0, 30);
            intervals.push_back({center - leftPad, center + rightPad});
        }
    } else if (mode == 1) {
        long long base = rnd.next(-80, -20);
        for (int i = 0; i < n; ++i) {
            long long l = base + i * rnd.next(3, 7) + rnd.next(0, 2);
            long long r = l + rnd.next(0, 2);
            intervals.push_back({l, r});
        }
    } else if (mode == 2) {
        long long l = rnd.next(-50, 0);
        long long r = rnd.next(0, 50);
        for (int i = 0; i < n; ++i) {
            intervals.push_back({l, r});
            l += rnd.next(0, 4);
            r -= rnd.next(0, 4);
            if (l > r) swap(l, r);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(-15, 15);
            long long radius = rnd.next(0, 4);
            intervals.push_back({x - radius, x + radius});
        }
    } else if (mode == 4) {
        const long long low = -1000000000LL;
        const long long high = 1000000000LL;
        for (int i = 0; i < n; ++i) {
            long long l = rnd.next(low, low + 100);
            long long r = rnd.next(high - 100, high);
            if (rnd.next(0, 3) == 0) {
                l = rnd.next(high - 100, high);
                r = l;
            }
            intervals.push_back({l, r});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(-100, 100);
            long long b = rnd.next(-100, 100);
            if (a > b) swap(a, b);
            intervals.push_back({a, b});
        }
    }

    shuffle(intervals.begin(), intervals.end());
    println(n, k);
    for (auto [l, r] : intervals) println(l, r);

    return 0;
}
