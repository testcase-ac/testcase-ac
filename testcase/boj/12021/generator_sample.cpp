#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_A = 1000000000000000000LL;

    int mode = rnd.next(0, 6);
    long long a = 1;
    long long b = 1;

    if (mode == 0) {
        a = rnd.next(1LL, 1000LL);
        b = a;
    } else if (mode == 1) {
        a = rnd.next(2LL, 1000000LL);
        b = rnd.next(1LL, a - 1);
    } else if (mode == 2) {
        a = rnd.next(2LL, MAX_A);
        long long gap = rnd.next(1LL, min(1000000LL, a - 1));
        b = a - gap;
    } else if (mode == 3) {
        a = rnd.next(2LL, MAX_A);
        b = rnd.next(1LL, min(1000000LL, a));
    } else if (mode == 4) {
        a = rnd.next(MAX_A - 1000000LL, MAX_A);
        b = rnd.next(1LL, a);
    } else if (mode == 5) {
        a = rnd.next(1LL, MAX_A / 1000000LL) * 1000000LL;
        b = rnd.next(1LL, a / 1000000LL) * 1000000LL;
    } else {
        a = rnd.next(1LL, MAX_A);
        b = rnd.next(1LL, a);
    }

    println(a, b);
    return 0;
}
