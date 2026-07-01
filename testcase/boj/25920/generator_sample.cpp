#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Tire {
    long long a;
    long long b;
    long long d;
};

Tire makeTire(long long maxPerformance, int mode) {
    if (mode == 0) {
        long long v = rnd.next(1LL, maxPerformance);
        long long d = rnd.next(1LL, maxPerformance);
        return {v, v, d};
    }

    long long d = rnd.next(1LL, max(1LL, maxPerformance / 8));
    long long steps = rnd.next(1LL, max(1LL, (maxPerformance - 1) / d));
    long long b = rnd.next(1LL, maxPerformance - steps * d);
    long long a = b + steps * d;
    return {a, b, d};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    long long l;
    long long maxPerformance;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
        l = rnd.next(1LL, 40LL);
        maxPerformance = 80;
    } else if (mode == 1) {
        n = rnd.next(5, 15);
        m = rnd.next(1, 25);
        l = rnd.next(20LL, 300LL);
        maxPerformance = 1000;
    } else if (mode == 2) {
        n = rnd.next(1, 8);
        m = rnd.next(60, 100);
        l = rnd.next(1LL, 1000000000LL);
        maxPerformance = 10000;
    } else if (mode == 3) {
        n = rnd.next(20, 60);
        m = rnd.next(1, 100);
        l = rnd.next(1LL, 1000000LL);
        maxPerformance = 1000000;
    } else {
        n = rnd.next(1, 20);
        m = rnd.next(1, 100);
        l = rnd.next(1LL, 1000000000LL);
        maxPerformance = 1000000000LL;
    }

    vector<Tire> tires;
    tires.reserve(n);
    for (int i = 0; i < n; ++i) {
        int tireMode = rnd.next(0, 3);
        if (mode == 4 && rnd.next(0, 3) == 0) {
            long long b = rnd.next(1LL, 1000000000LL);
            long long d = rnd.next(1LL, 1000000000LL);
            tires.push_back({b, b, d});
        } else {
            tires.push_back(makeTire(maxPerformance, tireMode));
        }
    }

    if (mode == 3) {
        shuffle(tires.begin(), tires.end());
    }

    println(n, m, l);
    for (const Tire& tire : tires) {
        println(tire.a, tire.b, tire.d);
    }

    return 0;
}
