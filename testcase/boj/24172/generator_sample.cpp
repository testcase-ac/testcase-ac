#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long makeValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 8);
    }
    if (mode == 1) {
        return rnd.next(1, 1000);
    }
    if (mode == 2) {
        return rnd.next(999999900LL, 1000000000LL);
    }
    if (mode == 3) {
        vector<long long> anchors = {1, 2, 3, 10, 1000000000LL};
        return rnd.any(anchors);
    }

    long long base = rnd.next(1, 1000000);
    long long multiplier = rnd.next(1, 1000);
    return min(1000000000LL, base * multiplier);
}

vector<long long> makeArray(int m, int mode) {
    vector<long long> values(m);

    if (mode == 0) {
        long long x = makeValue(rnd.next(0, 4));
        fill(values.begin(), values.end(), x);
        return values;
    }

    if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            values[i] = (i % 2 == 0 ? 1 : 1000000000LL);
        }
        if (rnd.next(0, 1)) {
            reverse(values.begin(), values.end());
        }
        return values;
    }

    if (mode == 2) {
        long long start = rnd.next(1, 20);
        long long step = rnd.next(0, 7);
        for (int i = 0; i < m; ++i) {
            values[i] = min(1000000000LL, start + step * i);
        }
        shuffle(values.begin(), values.end());
        return values;
    }

    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < m; ++i) {
        values[i] = makeValue(valueMode);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    int m;

    if (sizeMode == 0) {
        n = 1;
        m = rnd.next(1, 6);
    } else if (sizeMode == 1) {
        n = rnd.next(2, 8);
        m = 1;
    } else if (sizeMode == 2) {
        n = rnd.next(1, 12);
        m = rnd.next(2, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(250, 300);
        m = rnd.next(2, 20);
    } else if (sizeMode == 4) {
        n = rnd.next(1, 30);
        m = rnd.next(80, 160);
    } else {
        n = 300;
        m = rnd.next(2, 10);
    }

    vector<long long> a = makeArray(m, rnd.next(0, 3));
    vector<long long> b = makeArray(m, rnd.next(0, 3));

    if (rnd.next(0, 4) == 0) {
        b = a;
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
