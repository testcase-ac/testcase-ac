#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000;

int randomValueWithBit(int bit) {
    int value = 1 << bit;
    for (int b = 0; b < 20; ++b) {
        if (b != bit && rnd.next(0, 1)) value |= 1 << b;
    }
    return min(value, MAX_A);
}

int randomMask() {
    int value = 0;
    while (value == 0 || value > MAX_A) {
        value = 0;
        int bits = rnd.next(1, 7);
        for (int i = 0; i < bits; ++i) value |= 1 << rnd.next(0, 19);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a;

    if (mode == 0) {
        int sharedBit = rnd.next(0, 19);
        n = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) a.push_back(randomValueWithBit(sharedBit));
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a.push_back(1 << rnd.next(0, 19));
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        int pivot = rnd.next(0, 19);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, MAX_A);
            if (i % 3 == 0) value |= 1 << pivot;
            if (value > MAX_A) value = 1 << pivot;
            a.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) a.push_back(randomMask());
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        vector<int> pool = {1, 2, 3, 5, 7, 15, 31, 63, 127, 255, 511, 1023, MAX_A};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else {
        n = rnd.next(1, 12);
        int base = rnd.next(MAX_A - 100, MAX_A);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(max(1, base - 200), MAX_A));
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
