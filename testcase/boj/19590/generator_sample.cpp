#include "testlib.h"
#include <algorithm>
#include <cstdint>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<long long> x;

    if (mode == 0) {
        n = 1;
        x.push_back(rnd.next(1LL, 1000000000LL));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        long long rest = 0;
        for (int i = 1; i < n; ++i) {
            long long v = rnd.next(1LL, 80LL);
            x.push_back(v);
            rest += v;
        }
        x.push_back(rnd.next(rest + 1, min(1000000000LL, rest + 200)));
        shuffle(x.begin(), x.end());
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        long long target = rnd.next(2LL, 120LL);
        x.assign(n, 1);
        long long remaining = target - n;
        while (remaining > 0) {
            long long add = rnd.next(1LL, remaining);
            x[rnd.next(n)] += add;
            remaining -= add;
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        x.reserve(n);
        for (int i = 0; i < n; ++i) {
            x.push_back(rnd.next(1LL, 30LL));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        long long base = rnd.next(999999900LL, 1000000000LL);
        x.assign(n, base);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(max(1LL, base - 20), 1000000000LL);
        }
    } else if (mode == 5) {
        n = rnd.next(20, 60);
        x.reserve(n);
        for (int i = 0; i < n; ++i) {
            x.push_back(rnd.next(1LL, 1000LL));
        }
    } else {
        n = rnd.next(2, 100);
        long long a = rnd.next(1LL, 1000000000LL);
        long long b = rnd.next(1LL, 1000000000LL);
        x = {a, b};
        while ((int)x.size() < n) {
            x.push_back(rnd.next(1LL, 10LL));
        }
        shuffle(x.begin(), x.end());
    }

    println(n);
    for (long long v : x) {
        println(v);
    }

    return 0;
}
