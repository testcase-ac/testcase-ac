#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Interval = pair<long long, long long>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Interval> planks;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        long long right = rnd.next(1, 8);
        planks.push_back({0, right});
        for (int i = 1; i < n; ++i) {
            long long l = rnd.next(0LL, right);
            long long r = rnd.next(l + 1, right + rnd.next(1, 8));
            planks.push_back({l, r});
            right = max(right, r);
        }
    } else if (mode == 1) {
        int n = rnd.next(3, 12);
        long long l = 0;
        long long r = rnd.next(1, 5);
        planks.push_back({l, r});
        for (int i = 1; i < n; ++i) {
            long long len = r - l;
            long long gap = rnd.next(1LL, len + 2);
            l = r + gap;
            r = l + rnd.next(1, 7);
            planks.push_back({l, r});
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 14);
        long long cursor = 0;
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 8);
            long long l = cursor;
            long long r = l + len;
            planks.push_back({l, r});
            cursor = r + rnd.next(0, 4);
        }
        if (rnd.next(0, 1)) {
            planks.push_back({0, rnd.next(1, 4)});
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 10);
        planks.push_back({0, rnd.next(1, 20)});
        long long base = rnd.next(1000000000LL - 200, 1000000000LL - 20);
        for (int i = 1; i < n; ++i) {
            long long l = rnd.next(base, 999999999LL);
            long long r = rnd.next(l + 1, 1000000000LL);
            planks.push_back({l, r});
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 15);
        long long reach = rnd.next(2, 8);
        planks.push_back({0, reach});
        for (int i = 1; i < n; ++i) {
            long long l = rnd.next(0LL, reach + rnd.next(0, 5));
            long long r = rnd.next(l + 1, l + rnd.next(1, 10));
            planks.push_back({l, r});
            if (l <= reach) {
                reach = max(reach, r);
            }
        }
    } else {
        int n = rnd.next(2, 12);
        planks.push_back({0, rnd.next(1, 6)});
        for (int i = 1; i < n; ++i) {
            long long l = rnd.next(0LL, 40LL);
            long long r = rnd.next(l + 1, min(1000000000LL, l + rnd.next(1, 15)));
            planks.push_back({l, r});
        }
    }

    shuffle(planks.begin(), planks.end());

    println((int)planks.size());
    for (auto [l, r] : planks) {
        println(l, r);
    }

    return 0;
}
