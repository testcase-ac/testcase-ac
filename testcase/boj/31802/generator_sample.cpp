#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_VALUE = -1000000000;
const int MAX_VALUE = 1000000000;

int randomIntegral(int mode) {
    if (mode == 0) {
        return rnd.next(-5, 5);
    }
    if (mode == 1) {
        return rnd.next(-1000, 1000);
    }
    if (rnd.next(0, 4) == 0) {
        return rnd.next(0, 1) ? MIN_VALUE : MAX_VALUE;
    }
    return rnd.next(MIN_VALUE, MAX_VALUE);
}

int clampToLimit(long long value) {
    return (int)max((long long)MIN_VALUE, min((long long)MAX_VALUE, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p;
    if (mode == 0) {
        p = 1;
    } else if (mode == 1) {
        p = rnd.next(2, 5);
    } else if (mode == 5) {
        p = rnd.next(15, 30);
    } else {
        p = rnd.next(3, 12);
    }

    vector<int> integrals(p);
    int valueMode = rnd.next(0, 2);
    for (int i = 0; i < p; ++i) {
        integrals[i] = randomIntegral(valueMode);
    }

    if (mode == 2) {
        for (int i = 0; i < p; ++i) {
            integrals[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
        }
    } else if (mode == 3) {
        integrals[rnd.next(0, p - 1)] = MIN_VALUE;
        integrals[rnd.next(0, p - 1)] = MAX_VALUE;
    }

    int a, b;
    if (mode == 0) {
        a = rnd.next(0, 1) ? MIN_VALUE : rnd.next(-20, 20);
        b = rnd.next(0, 1) ? MAX_VALUE : rnd.next(a, min(MAX_VALUE, a + 50));
    } else if (mode == 1) {
        a = rnd.next(-30, 30);
        b = a;
    } else if (mode == 2) {
        a = rnd.next(-50, 0);
        b = rnd.next(0, 50);
    } else if (mode == 3) {
        a = rnd.next(-1000, 1000);
        b = clampToLimit((long long)a + rnd.next(p * 3, p * 20));
    } else if (mode == 4) {
        int base = rnd.next(-100, 100);
        int leftOffset = rnd.next(0, p - 1);
        int rightOffset = rnd.next(0, p - 1);
        a = base * p + leftOffset;
        b = base * p + rnd.next(0, 8) * p + rightOffset;
        if (b < a) {
            swap(a, b);
        }
    } else {
        a = rnd.next(MIN_VALUE, MAX_VALUE - 1000);
        b = rnd.next(a, min(MAX_VALUE, a + rnd.next(0, 1000)));
    }

    println(p);
    println(integrals);
    println(a, b);

    return 0;
}
