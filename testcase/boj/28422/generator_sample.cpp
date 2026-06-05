#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValue() {
    return rnd.next(1, 1023);
}

int patternedValue(int index, int mode) {
    if (mode == 0) return 1 << rnd.next(0, 9);
    if (mode == 1) return 1023 ^ (1 << rnd.next(0, 9));
    if (mode == 2) return (index % 2 == 0 ? 341 : 682);
    if (mode == 3) return (index % 3 == 0 ? 1023 : (index % 3 == 1 ? 512 : 511));
    if (mode == 4) return rnd.next(1, 31);
    return randomValue();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 9);
    } else if (mode == 3) {
        n = rnd.next(10, 30);
    } else {
        n = rnd.next(1, 24);
    }

    int targetRemainder = rnd.next(0, 2);
    if (mode >= 2 && rnd.next(0, 1)) {
        while (n > 1 && n % 3 != targetRemainder) --n;
    }

    vector<int> a(n);
    int valueMode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
        if (mode == 5 && i > 0 && rnd.next(0, 3) == 0) {
            a[i] = a[i - 1];
        } else {
            a[i] = patternedValue(i, valueMode);
        }
    }

    if (mode == 6) {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
