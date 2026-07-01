#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long randomValue(int scale) {
    if (scale == 0) return rnd.next(1, 30);
    if (scale == 1) return rnd.next(1, 1000000);
    return rnd.next(1LL, 1000000000LL);
}

int randomN() {
    int groups = rnd.next(1, 18);
    if (rnd.next(4) == 0) groups = rnd.next(18, 120);
    return 3 * groups + 1;
}

vector<long long> makeCase(int n, int mode) {
    int scale = rnd.next(0, 2);
    vector<long long> values(n);

    if (mode == 0) {
        for (long long& value : values) value = randomValue(scale);
    } else if (mode == 1) {
        long long start = randomValue(scale);
        long long step = rnd.next(1, scale == 2 ? 10000000 : 20);
        for (int i = 0; i < n; ++i) {
            values[i] = min(1000000000LL, start + step * i);
        }
    } else if (mode == 2) {
        long long start = randomValue(scale);
        long long step = rnd.next(1, scale == 2 ? 10000000 : 20);
        for (int i = 0; i < n; ++i) {
            values[i] = min(1000000000LL, start + step * (n - 1 - i));
        }
    } else if (mode == 3) {
        long long low = rnd.next(1, 1000);
        long long high = rnd.next(1000000000LL - 1000, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            values[i] = (i % 2 == 0) ? high - rnd.next(0, 1000) : low + rnd.next(0, 1000);
        }
    } else if (mode == 4) {
        long long base = randomValue(0);
        for (int i = 0; i < n; ++i) {
            values[i] = base + rnd.next(0, 5);
        }
        for (int i = 0; i < n; i += 3) {
            values[i] = rnd.next(500000000LL, 1000000000LL);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int block = i / 3;
            values[i] = rnd.next(1, 60) + 17LL * (block % 5);
        }
        if (rnd.next(2)) reverse(values.begin(), values.end());
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 15);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int n = randomN();
        if (caseIndex < 3) n = 4 + 3 * caseIndex;

        vector<long long> values = makeCase(n, caseIndex % 6);
        if (rnd.next(5) == 0) shuffle(values.begin(), values.end());

        println(n);
        println(values);
    }

    return 0;
}
