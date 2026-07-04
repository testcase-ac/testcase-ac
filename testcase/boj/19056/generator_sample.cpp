#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIM = 1000000000000LL;

long long clampValue(long long value) {
    return max(1LL, min(LIM, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long L = 1;
    long long R = 1;
    long long Q = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        L = rnd.next(1LL, 30LL);
        R = rnd.next(L, min(L + rnd.next(0LL, 20LL), LIM));
        Q = rnd.next(1LL, 30LL);
    } else if (mode == 1) {
        L = rnd.next(1LL, 80LL);
        R = L;
        Q = rnd.next(1LL, 120LL);
    } else if (mode == 2) {
        Q = rnd.next(2LL, 80LL);
        long long k = rnd.next(1LL, 20LL);
        long long boundary = k * Q;
        L = rnd.next(max(1LL, boundary - Q + 1), boundary);
        R = rnd.next(boundary, min(LIM, boundary + Q - 1));
    } else if (mode == 3) {
        Q = rnd.next(2LL, 100LL);
        long long k = rnd.next(1LL, 20LL);
        long long lo = (k - 1) * Q + 1;
        long long hi = k * Q - 1;
        L = rnd.next(max(1LL, lo), max(1LL, hi));
        R = rnd.next(L, max(L, hi));
    } else if (mode == 4) {
        R = rnd.next(1LL, 200LL);
        L = rnd.next(1LL, R);
        Q = rnd.next(R + 1, min(LIM, R + 200LL));
    } else if (mode == 5) {
        L = rnd.next(LIM - 200LL, LIM);
        R = rnd.next(L, LIM);
        Q = rnd.next(max(1LL, LIM - 200LL), LIM);
    } else {
        vector<long long> special = {1LL, 2LL, 3LL, 10LL, 999999999983LL, LIM - 1, LIM};
        L = rnd.any(special);
        R = rnd.next(L, LIM);
        Q = rnd.any(special);
    }

    L = clampValue(L);
    R = clampValue(R);
    Q = clampValue(Q);
    if (L > R) swap(L, R);

    println(L, R, Q);
    return 0;
}
