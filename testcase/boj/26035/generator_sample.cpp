#include "testlib.h"

using namespace std;

const long long MAX_NM = 1000000000000000000LL;

long long nearLimit() {
    return MAX_NM - rnd.next(0LL, 1000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    long long n;
    long long m;

    if (mode == 0) {
        n = rnd.next(2LL, 12LL);
        m = rnd.next(2LL, 12LL);
    } else if (mode == 1) {
        n = 2;
        m = rnd.next(2LL, 1000LL);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 2) {
        n = rnd.next(2LL, 1000LL);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(2LL, 1000LL);
        m = rnd.next(1000000LL, 1000000000LL);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 4) {
        n = nearLimit();
        m = nearLimit();
    } else if (mode == 5) {
        n = rnd.next(2LL, 1000000LL) * 1000000007LL + rnd.next(0LL, 20LL);
        m = rnd.next(2LL, 1000000LL) * 1000000006LL + rnd.next(0LL, 20LL);
        n = min(n, MAX_NM);
        m = min(m, MAX_NM);
    } else {
        n = rnd.next(2LL, MAX_NM);
        m = rnd.next(2LL, MAX_NM);
    }

    println(n, m);
    return 0;
}
