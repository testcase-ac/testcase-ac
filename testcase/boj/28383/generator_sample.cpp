#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 10000000000LL;
    long long n = 0;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.any(vector<long long>{0, 1, 2, 3, 4, 5, 10});
    } else if (mode == 1) {
        n = MAX_N - rnd.next(0LL, 1000LL);
    } else if (mode == 2) {
        long long x = rnd.next(0LL, 100000LL);
        n = x * x;
    } else if (mode == 3) {
        long long x = rnd.next(1LL, 100000LL);
        long long delta = rnd.next(-1000LL, 1000LL);
        n = max(0LL, min(MAX_N, x * x + delta));
    } else if (mode == 4) {
        vector<long long> powers;
        long long v = 1;
        while (v <= MAX_N) {
            powers.push_back(v);
            v *= 10;
        }
        n = rnd.any(powers);
    } else if (mode == 5) {
        long long base = rnd.next(1LL, 1000000LL);
        long long multiplier = rnd.next(1LL, 10000LL);
        n = min(MAX_N, base * multiplier);
    } else if (mode == 6) {
        n = rnd.next(0LL, 1000000LL);
    } else {
        n = rnd.next(0LL, MAX_N);
    }

    println(n);
    return 0;
}
