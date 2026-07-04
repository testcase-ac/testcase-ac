#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;
    int mode = rnd.next(0, 7);

    long long D = 1;
    long long P = 1;
    long long Q = 1;

    if (mode == 0) {
        P = rnd.next(1, 50);
        Q = rnd.next(1, 50);
        D = rnd.next(1, 300);
    } else if (mode == 1) {
        P = rnd.next(1, 1000);
        Q = P;
        D = rnd.next(1, 200000);
    } else if (mode == 2) {
        P = rnd.next(1, 1000);
        Q = rnd.next(1, 1000);
        long long a = rnd.next(0, 1000);
        long long b = rnd.next(0, 1000);
        long long exact = a * P + b * Q;
        D = max(1LL, exact);
    } else if (mode == 3) {
        long long g = rnd.next(2, 1000);
        P = g * rnd.next(1, 1000000);
        Q = g * rnd.next(1, 1000000);
        long long base = g * rnd.next(1, 1000000);
        D = min(LIMIT, base + rnd.next(1LL, g - 1));
    } else if (mode == 4) {
        P = rnd.next(1, 100000);
        Q = rnd.next(1, 100000);
        long long upper = min(LIMIT, max(P, Q) * rnd.next(1LL, 20LL));
        D = rnd.next(1LL, upper);
    } else if (mode == 5) {
        P = rnd.next(1, 1000000000);
        Q = rnd.next(1, 1000000000);
        D = rnd.next(900000000, 1000000000);
    } else if (mode == 6) {
        P = 1;
        Q = rnd.next(1, 1000000000);
        D = rnd.next(1, 1000000000);
    } else {
        P = rnd.next(999900000, 1000000000);
        Q = rnd.next(1, 1000);
        D = rnd.next(1, 1000000000);
    }

    if (rnd.next(0, 1)) swap(P, Q);

    println(D, P, Q);
    return 0;
}
