#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int signedValue(int x) {
    if (x == 0 || rnd.next(2) == 0) {
        return x;
    }
    return -x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(3, 20);
    }

    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = rnd.next(1, n);
    } else if (mode == 2) {
        m = n;
    } else if (mode == 3) {
        m = rnd.next(1, min(n, 4));
    } else {
        m = rnd.next(1, n);
    }

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        a.push_back(signedValue(rnd.next(0, 1023)));
    } else if (mode == 1) {
        int limit = rnd.next(0, 7);
        for (int i = 0; i < n; ++i) {
            a.push_back(signedValue(rnd.next(0, limit)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 9);
            int x = 1 << bit;
            if (rnd.next(4) == 0) {
                x = 0;
            }
            a.push_back(signedValue(x));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1000, 1023);
            a.push_back(signedValue(x));
        }
    } else if (mode == 4) {
        int base = rnd.next(0, 1023);
        for (int i = 0; i < n; ++i) {
            int noise = rnd.next(0, 31);
            a.push_back(signedValue((base ^ noise) & 1023));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(signedValue(rnd.next(0, 1023)));
        }
    }

    println(n, m);
    println(a);

    return 0;
}
