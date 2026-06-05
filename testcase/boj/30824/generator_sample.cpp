#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_X = 10000000000000000LL;

    vector<long long> fib = {1, 1};
    while (fib.back() <= MAX_X) {
        long long next = fib[fib.size() - 1] + fib[fib.size() - 2];
        if (next > MAX_X) break;
        fib.push_back(next);
    }
    int fibCount = static_cast<int>(fib.size());

    int T = rnd.next(12, 40);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int k = rnd.next(1, 3);
        long long x = 1;

        if (mode == 0) {
            x = 0;
            for (int i = 0; i < k; ++i) {
                int idx = rnd.next(0, min(20, fibCount - 1));
                x += fib[idx];
            }
        } else if (mode == 1) {
            x = 0;
            for (int i = 0; i < k; ++i) {
                int idx = rnd.next(max(0, fibCount - 15), fibCount - 1);
                x += fib[idx];
            }
            if (x > MAX_X) x = MAX_X - rnd.next(0, 1000);
        } else if (mode == 2) {
            x = rnd.next(1LL, 120LL);
        } else if (mode == 3) {
            long long base = fib[rnd.next(0, fibCount - 1)];
            long long delta = rnd.next(-3LL, 3LL);
            x = base + delta;
            if (x < 1) x = 1;
        } else if (mode == 4) {
            x = MAX_X - rnd.next(0LL, 1000000LL);
        } else {
            long long hi = rnd.next(1000000LL, MAX_X);
            long long lo = rnd.next(1LL, hi);
            x = rnd.next(lo, hi);
        }

        if (x < 1) x = 1;
        if (x > MAX_X) x = MAX_X;
        println(k, x);
    }

    return 0;
}
