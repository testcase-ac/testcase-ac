#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMax = 1000000000000000000LL;
    vector<long long> fib = {1, 2};
    while (fib.back() <= kMax - fib[fib.size() - 2]) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    long long k = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        k = rnd.next(1LL, 30LL);
    } else if (mode == 1) {
        long long boundary = rnd.any(fib);
        long long delta = rnd.next(-3LL, 3LL);
        k = min(kMax, max(1LL, boundary + delta));
    } else if (mode == 2) {
        long long prefix = rnd.next(1LL, 999LL);
        int zeros = rnd.next(0, 15);
        k = prefix;
        while (zeros-- > 0 && k <= kMax / 10) {
            k *= 10;
        }
        k = min(kMax, k + rnd.next(0LL, min(999LL, kMax - k)));
    } else if (mode == 3) {
        k = rnd.next(max(1LL, kMax - 1000000LL), kMax);
    } else if (mode == 4) {
        k = rnd.next(1LL, 1000000000000LL);
    } else {
        k = rnd.next(1LL, kMax);
    }

    println(k);
    return 0;
}
