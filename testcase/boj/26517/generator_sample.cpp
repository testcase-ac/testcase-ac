#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_VALUE = -10000000;
const int MAX_VALUE = 10000000;

int nonzeroInt(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x == 0) x = (hi > 0 ? 1 : -1);
    return x;
}

int smallNonzero() {
    return nonzeroInt(-20, 20);
}

int boundedInt() {
    vector<int> special = {MIN_VALUE, -1000, -20, -1, 0, 1, 20, 1000, MAX_VALUE};
    if (rnd.next(100) < 35) return rnd.any(special);
    return rnd.next(MIN_VALUE, MAX_VALUE);
}

int boundedNonzero() {
    int x = boundedInt();
    if (x == 0) x = rnd.next(2) == 0 ? -1 : 1;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int k, a, b, c, d;

    if (mode == 0) {
        k = boundedInt();
        a = boundedNonzero();
        b = boundedInt();
        c = a;
        d = b;
    } else if (mode == 1) {
        k = rnd.next(-1000, 1000);
        a = smallNonzero();
        c = smallNonzero();
        b = rnd.next(-100000, 100000);
        long long target = 1LL * a * k + b;
        long long candidateD = target - 1LL * c * k;
        if (candidateD < MIN_VALUE || candidateD > MAX_VALUE) {
            c = a;
            candidateD = b;
        }
        d = static_cast<int>(candidateD);
    } else if (mode == 2) {
        k = rnd.next(-50, 50);
        a = smallNonzero();
        c = smallNonzero();
        b = rnd.next(-1000, 1000);
        d = rnd.next(-1000, 1000);
        if (1LL * a * k + b == 1LL * c * k + d) {
            d += (d == MAX_VALUE ? -1 : 1);
        }
    } else if (mode == 3) {
        vector<int> endpoints = {MIN_VALUE, MAX_VALUE};
        k = rnd.any(endpoints);
        a = rnd.any(endpoints);
        c = rnd.any(endpoints);
        b = rnd.any(endpoints);
        d = rnd.any(endpoints);
    } else {
        k = boundedInt();
        a = boundedNonzero();
        c = boundedNonzero();
        b = boundedInt();
        d = boundedInt();
    }

    println(k);
    println(a, b, c, d);

    return 0;
}
