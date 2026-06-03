#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;
    const long long MAX_P = 1000000007LL;

    int mode = rnd.next(0, 7);
    int k;
    long long n;

    if (mode == 0) {
        k = rnd.next(1, 5);
        n = rnd.next(k + 1, k + 12);
    } else if (mode == 1) {
        k = 1;
        n = rnd.next(2LL, 1000000000LL);
    } else if (mode == 2) {
        k = rnd.next(1, 100);
        n = k + 1;
    } else if (mode == 3) {
        k = rnd.next(2, 20);
        n = rnd.next(1000000LL, 1000000000LL);
    } else if (mode == 4) {
        k = 100;
        n = rnd.next(101LL, 1000000000LL);
    } else if (mode == 5) {
        k = rnd.next(90, 100);
        n = rnd.next(k + 1LL, k + 200LL);
    } else if (mode == 6) {
        k = rnd.next(1, 100);
        n = rnd.next(k + 1LL, 1000000000LL);
    } else {
        k = rnd.next(1, 30);
        n = rnd.wnext(1000000000LL - k, 3) + k + 1;
    }

    long long p;
    int pMode = rnd.next(0, 5);
    if (pMode == 0) {
        p = 1;
    } else if (pMode == 1) {
        p = MAX_P;
    } else if (pMode == 2) {
        p = rnd.next(2LL, 20LL);
    } else if (pMode == 3) {
        p = rnd.next(21LL, 100000LL);
    } else {
        p = rnd.next(1LL, MAX_P);
    }

    vector<long long> a(k);
    int aMode = rnd.next(0, 5);
    for (int i = 0; i < k; ++i) {
        if (aMode == 0) {
            a[i] = rnd.next(1LL, min(MAX_VALUE, max(1LL, p)));
        } else if (aMode == 1) {
            a[i] = rnd.next(1LL, 20LL);
        } else if (aMode == 2) {
            a[i] = MAX_VALUE - rnd.next(0LL, 1000LL);
        } else if (aMode == 3) {
            a[i] = (i % 2 == 0 ? 1LL : MAX_VALUE);
        } else {
            a[i] = rnd.next(1LL, MAX_VALUE);
        }
    }

    println(n, k);
    println(a);
    println(p);

    return 0;
}
