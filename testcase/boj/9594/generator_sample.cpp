#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;

    vector<long long> values;

    int mode = rnd.next(0, 4);
    int count = rnd.next(6, 24);

    if (mode == 0) {
        for (int i = 0; i < count; ++i) values.push_back(rnd.next(0LL, 2000LL));
    } else if (mode == 1) {
        long long p = 1;
        while (p <= MAX_N / 5 && rnd.next(0, 1)) p *= 5;

        for (int i = 0; i < count; ++i) {
            long long delta = rnd.next(-12LL, 12LL);
            long long candidate = p + delta;
            values.push_back(min(MAX_N, max(0LL, candidate)));
        }
    } else if (mode == 2) {
        long long p = 1;
        while (p <= MAX_N / 5) p *= 5;

        for (int i = 0; i < count; ++i) {
            long long delta = rnd.next(0LL, 1000000LL);
            values.push_back(MAX_N - delta);
        }
        values.push_back(p);
        values.push_back(p - 1);
    } else if (mode == 3) {
        long long base = rnd.next(0LL, MAX_N - count * 10LL);
        long long step = rnd.next(1LL, 10LL);
        for (int i = 0; i < count; ++i) values.push_back(base + i * step);
    } else {
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 3) == 0) {
                long long p = 1;
                int exponent = rnd.next(0, 25);
                for (int e = 0; e < exponent && p <= MAX_N / 5; ++e) p *= 5;
                values.push_back(min(MAX_N, max(0LL, p + rnd.next(-3LL, 3LL))));
            } else {
                values.push_back(rnd.next(0LL, MAX_N));
            }
        }
    }

    shuffle(values.begin(), values.end());
    for (long long value : values) println(value);
    println(-1);

    return 0;
}
