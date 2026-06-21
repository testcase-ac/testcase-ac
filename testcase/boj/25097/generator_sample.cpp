#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long jitter(long long base, long long radius) {
    long long lo = max(1LL, base - radius);
    long long hi = min(1000000000LL, base + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(2, mode == 5 ? 30 : 12);
        int p = rnd.next(2, mode == 5 ? 20 : 8);
        println(n, p);

        long long lowBand = rnd.next(1LL, 200LL);
        long long highBand = rnd.next(999999800LL, 1000000000LL);
        long long center = rnd.next(100000LL, 999900000LL);

        for (int i = 0; i < n; ++i) {
            vector<long long> row;
            row.reserve(p);

            if (mode == 0) {
                long long value = rnd.next(1, 1000000000);
                row.assign(p, value);
            } else if (mode == 1) {
                long long lo = jitter(center + i * rnd.next(-2000LL, 2000LL), 5000);
                long long hi = jitter(lo + rnd.next(0LL, 20000LL), 3000);
                for (int j = 0; j < p; ++j) {
                    row.push_back(rnd.next(min(lo, hi), max(lo, hi)));
                }
            } else if (mode == 2) {
                for (int j = 0; j < p; ++j) {
                    row.push_back((j + i) % 2 == 0 ? jitter(lowBand, 80) : jitter(highBand, 80));
                }
            } else if (mode == 3) {
                long long start = rnd.next(1LL, 1000000000LL - p - n);
                long long step = rnd.next(1LL, 1000LL);
                for (int j = 0; j < p; ++j) {
                    row.push_back(min(1000000000LL, start + step * (i + j)));
                }
            } else if (mode == 4) {
                long long lo = rnd.next(1LL, 1000000LL);
                long long hi = rnd.next(999000000LL, 1000000000LL);
                row.push_back(lo);
                row.push_back(hi);
                while ((int)row.size() < p) {
                    row.push_back(rnd.next(0, 1) ? jitter(lo, 1000) : jitter(hi, 1000));
                }
            } else {
                long long base = rnd.next(1LL, 1000000000LL);
                for (int j = 0; j < p; ++j) {
                    row.push_back(jitter(base, 1000000));
                }
            }

            shuffle(row.begin(), row.end());
            println(row);
        }
    }

    return 0;
}
