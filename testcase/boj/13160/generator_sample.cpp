#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<pair<long long, long long>> intervals;

    if (mode == 0) {
        long long p = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(1LL, p - 1);
            long long e = rnd.next(p, p + 25);
            intervals.push_back({s, e});
        }
    } else if (mode == 1) {
        long long base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            long long s = base + i * rnd.next(2, 5);
            long long e = s + rnd.next(1, 3);
            intervals.push_back({s, e});
        }
    } else if (mode == 2) {
        long long left = rnd.next(1, 20);
        long long right = left + rnd.next(2 * n + 1, 2 * n + 30);
        for (int i = 0; i < n; ++i) {
            intervals.push_back({left + i, right - i});
        }
    } else if (mode == 3) {
        long long start = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long s = start + rnd.next(0, 4);
            long long e = s + rnd.next(1, 8);
            intervals.push_back({s, e});
            start += rnd.next(1, 4);
        }
    } else if (mode == 4) {
        long long p = rnd.next(3, 50);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                long long s = rnd.next(1LL, p - 1);
                intervals.push_back({s, p});
            } else {
                long long e = rnd.next(p + 1, p + 30);
                intervals.push_back({p, e});
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(1LL, 1000000000LL - 100);
            long long e = s + rnd.next(1, 100);
            intervals.push_back({s, e});
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(n);
    for (auto [s, e] : intervals) {
        println(s, e);
    }

    return 0;
}
