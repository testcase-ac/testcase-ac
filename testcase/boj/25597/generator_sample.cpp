#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    int mode = rnd.next(0, 8);
    long long X = 1, T = 1;

    if (mode == 0) {
        X = rnd.next(1LL, 40LL);
        T = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        X = rnd.next(1LL, 80LL);
        T = rnd.next(1LL, (X + 7) / 8);
    } else if (mode == 2) {
        T = rnd.next(1LL, 20LL);
        X = rnd.next(8 * T + 1, 8 * T + 40);
    } else if (mode == 3) {
        T = rnd.next(1LL, 25LL);
        long long speed = rnd.any(std::vector<long long>{1, 4, 8});
        X = speed * rnd.next(1LL, T);
    } else if (mode == 4) {
        long long q = rnd.next(1LL, 1000000LL);
        long long r = rnd.next(0LL, 7LL);
        X = 8 * q + r;
        T = q + rnd.next(0LL, 20LL);
    } else if (mode == 5) {
        X = rnd.next(LIM - 200, LIM);
        T = rnd.next(1LL, 200LL);
    } else if (mode == 6) {
        T = rnd.next(LIM - 200, LIM);
        X = rnd.next(1LL, 200LL);
    } else {
        X = rnd.next(1LL, LIM);
        long long minTime = (X + 7) / 8;
        T = rnd.next(std::max(1LL, minTime - 5), std::min(LIM, minTime + 25));
    }

    println(X, T);
    return 0;
}
