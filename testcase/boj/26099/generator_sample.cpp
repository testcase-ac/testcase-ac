#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_N = 3;
    const long long MAX_N = 1000000000000000000LL;

    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(MIN_N, 50LL);
    } else if (mode == 1) {
        n = rnd.any(vector<long long>{4, 7});
    } else if (mode == 2) {
        long long base = rnd.next(0LL, 199999999999999999LL) * 5;
        n = base + rnd.next(0LL, 4LL);
        if (n < MIN_N) n += 5;
    } else if (mode == 3) {
        long long bags5 = rnd.next(0LL, 200000000000000000LL);
        long long bags3 = rnd.next(0LL, 4LL);
        n = 5 * bags5 + 3 * bags3;
        if (n < MIN_N) n += 3;
        if (n > MAX_N) n = MAX_N - rnd.next(0LL, 20LL);
    } else if (mode == 4) {
        n = MAX_N - rnd.next(0LL, 100LL);
    } else {
        long long q = rnd.next(1LL, 333333333333333333LL);
        n = 3 * q;
    }

    println(n);
    return 0;
}
