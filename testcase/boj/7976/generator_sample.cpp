#include "testlib.h"
#include <vector>
using namespace std;

long long valueWithParity(int parity, int profile) {
    if (profile == 0) {
        return parity;
    }
    if (profile == 1) {
        return rnd.next(0, 50) * 2LL + parity;
    }
    if (profile == 2) {
        return 1000000000LL - ((1000000000LL & 1) != parity);
    }
    return rnd.next(0, 500000000) * 2LL + parity;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = n;
    } else if (mode == 3) {
        k = rnd.next(2, 10);
        n = rnd.next(k, min(60, k * rnd.next(2, 8)));
    } else if (mode == 4) {
        k = rnd.next(2, 20);
        n = rnd.next(k, 80);
    } else {
        n = rnd.next(50, 120);
        k = rnd.next(1, n);
    }

    vector<int> residueParity(k);
    int paritySum = 0;
    for (int i = 0; i < k; ++i) {
        residueParity[i] = rnd.next(0, 1);
        paritySum ^= residueParity[i];
    }
    if (mode == 3 && paritySum == 1) {
        residueParity[rnd.next(0, k - 1)] ^= 1;
    }

    vector<long long> a(n);
    int profile = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        int parity;
        if (mode == 0) {
            parity = rnd.next(0, 1);
        } else if (mode == 1) {
            parity = rnd.next(0, 1);
        } else if (mode == 2) {
            parity = rnd.next(0, 1);
        } else {
            parity = residueParity[i % k];
            if (mode == 4 && rnd.next(0, 4) == 0) {
                parity ^= 1;
            }
        }
        a[i] = valueWithParity(parity, profile);
    }

    println(n, k);
    println(a);
    return 0;
}
