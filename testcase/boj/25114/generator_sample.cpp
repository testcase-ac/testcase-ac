#include "testlib.h"

#include <vector>

using namespace std;

const int MAX_VALUE = (1 << 30) - 1;

int randomValue(int bitLimit) {
    int limit = (1 << bitLimit) - 1;
    return rnd.next(0, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(2, 20);
    }

    int bitLimit = rnd.next(1, 30);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = randomValue(bitLimit);
        b[i] = a[i];
    }

    if (mode == 0) {
        if (rnd.next(0, 1) == 1) {
            b[0] ^= 1 << rnd.next(0, 29);
        }
    } else {
        int operations;
        if (mode == 1) {
            operations = rnd.next(0, n - 1);
        } else if (mode == 2) {
            operations = rnd.next(n, 3 * n);
        } else if (mode == 3) {
            operations = n - 1;
        } else {
            operations = rnd.next(1, 2 * n);
        }

        for (int step = 0; step < operations; ++step) {
            int i;
            if (mode == 3) {
                i = step % (n - 1);
            } else {
                i = rnd.next(0, n - 2);
            }
            int x = randomValue(bitLimit);
            if (x == 0 && rnd.next(0, 2) != 0) {
                x = 1 << rnd.next(0, bitLimit - 1);
            }
            b[i] ^= x;
            b[i + 1] ^= x;
        }

        if (mode == 4 || mode == 5) {
            int pos = rnd.next(0, n - 1);
            int bit = rnd.next(0, 29);
            b[pos] ^= 1 << bit;
        }
    }

    for (int i = 0; i < n; ++i) {
        a[i] &= MAX_VALUE;
        b[i] &= MAX_VALUE;
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
