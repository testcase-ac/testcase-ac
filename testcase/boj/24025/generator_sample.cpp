#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int signedValue(int n, int sign, int magnitude) {
    magnitude = max(1, min(n, magnitude));
    return sign * magnitude;
}

int randomMagnitude(int n, int mode) {
    if (n == 1) return 1;
    if (mode == 0) return rnd.next(1, min(n, 3));
    if (mode == 1) return rnd.next(max(1, n - 3), n);
    return rnd.next(1, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 80);
    } else {
        n = rnd.next(200, 700);
    }

    vector<int> a(n);
    int mode = rnd.next(7);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = signedValue(n, 1, randomMagnitude(n, rnd.next(3)));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int sign = (i + rnd.next(2)) % 2 == 0 ? 1 : -1;
            a[i] = signedValue(n, sign, randomMagnitude(n, rnd.next(3)));
        }
    } else if (mode == 2) {
        int firstBreak = rnd.next(0, n - 1);
        int secondBreak = rnd.next(firstBreak, n - 1);
        for (int i = 0; i < n; ++i) {
            int sign = (i <= firstBreak || i > secondBreak) ? 1 : -1;
            a[i] = signedValue(n, sign, randomMagnitude(n, i % 3));
        }
    } else if (mode == 3) {
        int sign = rnd.next(2) == 0 ? 1 : -1;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(100) < 35) sign *= -1;
            a[i] = signedValue(n, sign, randomMagnitude(n, rnd.next(3)));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(100) < 75 ? 1 : -1;
            int magnitude = (i % 2 == 0) ? i + 1 : n - i;
            a[i] = signedValue(n, sign, magnitude);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(100) < 75 ? -1 : 1;
            a[i] = signedValue(n, sign, rnd.any(vector<int>{1, n}));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(2) == 0 ? 1 : -1;
            a[i] = signedValue(n, sign, randomMagnitude(n, 2));
        }
    }

    println(n);
    println(a);

    return 0;
}
