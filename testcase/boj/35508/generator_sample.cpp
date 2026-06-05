#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Dish {
    long long t;
    long long a;
    long long b;
};

long long scoreValue(int profile, int index, int n) {
    const long long high = 1000000000LL;
    if (profile == 0) return rnd.next(1, 30);
    if (profile == 1) return rnd.next(high - 50, high);
    if (profile == 2) return min(high, 1LL + index * (high / max(1, n)));
    return max(1LL, high - index * (high / max(1, n + 1)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 20);
    long long d = rnd.next(1LL, 1000000000LL);
    vector<Dish> dishes;

    if (mode == 0) {
        n = 1;
        d = rnd.next(1LL, 1000000000LL);
        dishes.push_back({rnd.next(1LL, d), rnd.next(1LL, 1000000000LL), rnd.next(1LL, 1000000000LL)});
    } else if (mode == 1) {
        d = rnd.next(1LL, 60LL);
        for (int i = 0; i < n; ++i) {
            long long t = rnd.next(1LL, d);
            dishes.push_back({t, rnd.next(1LL, 200LL), rnd.next(1LL, 200LL)});
        }
    } else if (mode == 2) {
        d = rnd.next(2LL, 1000000000LL);
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            long long t = (i % 3 == 0 ? d : rnd.next(1LL, d));
            dishes.push_back({t, rnd.next(1LL, 1000000000LL), rnd.next(1LL, 1000000000LL)});
        }
    } else if (mode == 3) {
        d = rnd.next(2LL, 1000LL);
        n = rnd.next(2, 20);
        long long left = rnd.next(1LL, d - 1);
        long long right = d - left;
        dishes.push_back({left, 1000000000LL, 1});
        dishes.push_back({right, 1, 1000000000LL});
        for (int i = 2; i < n; ++i) {
            long long t = rnd.next(1LL, d);
            dishes.push_back({t, rnd.next(1LL, 1000LL), rnd.next(1LL, 1000LL)});
        }
    } else if (mode == 4) {
        d = rnd.next(10LL, 1000000000LL);
        n = rnd.next(3, 25);
        for (int i = 0; i < n; ++i) {
            long long span = min(d, 30LL);
            long long t = d - rnd.next(0LL, span - 1);
            dishes.push_back({t, scoreValue(i % 4, i + 1, n), scoreValue((i + 2) % 4, n - i, n)});
        }
    } else {
        d = rnd.next(1LL, 1000000000LL);
        n = rnd.next(30, 80);
        long long maxSmallTime = min(d, 1000LL);
        for (int i = 0; i < n; ++i) {
            long long t = rnd.next(1LL, maxSmallTime);
            if (rnd.next(0, 5) == 0) t = d;
            dishes.push_back({t, rnd.next(1LL, 1000000000LL), rnd.next(1LL, 1000000000LL)});
        }
    }

    shuffle(dishes.begin(), dishes.end());

    println((int)dishes.size(), d);
    for (const Dish& dish : dishes) {
        println(dish.t, dish.a, dish.b);
    }

    return 0;
}
