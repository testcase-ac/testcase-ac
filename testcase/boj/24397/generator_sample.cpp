#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAXV = 1000000000;

int clampValue(long long x) {
    if (x < 1) return 1;
    if (x > MAXV) return MAXV;
    return static_cast<int>(x);
}

int randomBitPattern() {
    int mode = rnd.next(5);
    if (mode == 0) return rnd.next(1, 64);
    if (mode == 1) {
        int bit = rnd.next(0, 29);
        return clampValue((1LL << bit) + rnd.next(-3, 3));
    }
    if (mode == 2) {
        int bit = rnd.next(1, 29);
        return clampValue((1LL << bit) - 1 + rnd.next(-2, 2));
    }
    if (mode == 3) return rnd.next(1, 1024);
    return rnd.next(MAXV - 2000, MAXV);
}

vector<int> makeArray(int size, int mode, int base, int span) {
    vector<int> values;
    values.reserve(size);

    for (int i = 0; i < size; ++i) {
        int x;
        if (mode == 0) {
            x = rnd.next(1, 64);
        } else if (mode == 1) {
            x = clampValue(base + rnd.next(-span, span));
        } else if (mode == 2) {
            x = randomBitPattern();
        } else {
            x = rnd.next(1, MAXV);
        }
        values.push_back(x);
    }

    if (mode == 1 && size >= 2) {
        values[rnd.next(size)] = base;
        values[rnd.next(size)] = clampValue(base ^ rnd.next(0, 31));
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);

    if (mode == 3) {
        n = rnd.next(20, 45);
        m = rnd.next(20, 45);
    }

    int bit = rnd.next(1, 29);
    int base = clampValue((1LL << bit) + rnd.next(-16, 16));
    int span = rnd.next(0, 24);

    int k;
    if (mode == 0) {
        k = rnd.next(1, 128);
    } else if (mode == 1) {
        k = clampValue((1LL << bit) + rnd.next(-8, 8));
    } else if (mode == 2) {
        k = rnd.any(vector<int>{1, 2, 3, 7, 8, 15, 16, 31, 32, 63, 64, 127, 128});
    } else {
        k = rnd.next(MAXV - 2000, MAXV);
    }

    vector<int> a = makeArray(n, mode, base, span);
    vector<int> b = makeArray(m, mode == 0 ? 0 : rnd.next(1, 4), base ^ rnd.next(0, 31), span);

    println(n, m, k);
    println(a);
    println(b);

    return 0;
}
