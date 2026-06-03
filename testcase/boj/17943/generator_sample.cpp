#include "testlib.h"

#include <vector>
using namespace std;

const int MAX_VALUE = 2147483647;

int randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(0, 15);
    }
    if (mode == 1) {
        vector<int> values = {0, 1, 2, 3, 7, 15, 255, 1023, MAX_VALUE};
        return rnd.any(values);
    }
    if (mode == 2) {
        return rnd.next(0, (1 << rnd.next(1, 16)) - 1);
    }
    return rnd.next(0, MAX_VALUE);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 3);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(3, 6);
    } else if (sizeMode == 1) {
        n = rnd.next(7, 15);
    } else {
        n = rnd.next(16, 30);
    }

    int q = rnd.next(1, min(40, 2 * n + 10));
    int valueMode = rnd.next(0, 3);

    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        a[i] = randomValue(valueMode);
    }

    println(n, q);
    println(a);

    for (int i = 0; i < q; ++i) {
        int type = rnd.next(0, 1);
        int x, y;

        int rangeMode = rnd.next(0, 5);
        if (rangeMode == 0) {
            x = y = rnd.next(1, n);
        } else if (rangeMode == 1) {
            x = 1;
            y = rnd.next(1, n);
        } else if (rangeMode == 2) {
            x = rnd.next(1, n);
            y = n;
        } else if (rangeMode == 3) {
            x = 1;
            y = n;
        } else {
            x = rnd.next(1, n);
            y = rnd.next(x, n);
        }

        if (type == 0) {
            println(type, x, y);
        } else {
            println(type, x, y, randomValue(valueMode));
        }
    }

    return 0;
}
