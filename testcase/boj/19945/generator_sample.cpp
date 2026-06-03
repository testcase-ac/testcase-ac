#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMinInt = -2147483648LL;
    const long long kMaxInt = 2147483647LL;

    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(kMinInt, -1LL);
    } else if (mode == 1) {
        n = rnd.next(0LL, 1LL);
    } else if (mode == 2) {
        int bit = rnd.next(1, 30);
        long long power = 1LL << bit;
        n = power + rnd.next(-2LL, 2LL);
    } else if (mode == 3) {
        int bit = rnd.next(0, 30);
        long long upper = (1LL << (bit + 1)) - 1;
        long long lower = 1LL << bit;
        n = rnd.next(lower, upper);
    } else if (mode == 4) {
        n = rnd.next(kMaxInt - 32, kMaxInt);
    } else {
        n = rnd.next(kMinInt, kMaxInt);
    }

    println(n);
    return 0;
}
