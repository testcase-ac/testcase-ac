#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;

    vector<long long> powers3;
    for (long long x = 1; x <= MAX_N; x *= 3) {
        powers3.push_back(x);
        if (x > MAX_N / 3) break;
    }

    vector<long long> queries;
    int mode = rnd.next(0, 4);
    int q = rnd.next(1, 30);

    if (mode == 0) {
        q = rnd.next(1, 12);
        for (int i = 0; i < q; ++i) {
            queries.push_back(rnd.next(1LL, 120LL));
        }
    } else if (mode == 1) {
        q = rnd.next(3, 18);
        for (int i = 0; i < q; ++i) {
            long long p = rnd.any(powers3);
            long long delta = rnd.next(-4LL, 4LL);
            long long n = min(MAX_N, max(1LL, p + delta));
            queries.push_back(n);
        }
    } else if (mode == 2) {
        q = rnd.next(3, 18);
        for (int i = 0; i < q; ++i) {
            long long base = rnd.next(1LL, MAX_N / 3);
            long long rem = rnd.next(0LL, 2LL);
            queries.push_back(3 * base + rem);
        }
    } else if (mode == 3) {
        q = rnd.next(1, 16);
        for (int i = 0; i < q; ++i) {
            queries.push_back(MAX_N - rnd.next(0LL, 1000LL));
        }
    } else {
        for (int i = 0; i < q; ++i) {
            queries.push_back(rnd.next(1LL, MAX_N));
        }
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(queries.begin(), queries.end());
    }

    println(static_cast<int>(queries.size()));
    for (long long n : queries) {
        println(n);
    }

    return 0;
}
