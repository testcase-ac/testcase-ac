#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<long long> makeIncreasing(int n) {
    vector<long long> values(n);
    long long cur = rnd.next(-20, 20);
    for (int i = 0; i < n; ++i) {
        cur += rnd.next(0, 7);
        values[i] = cur;
    }
    return values;
}

vector<long long> makeDecreasing(int n) {
    vector<long long> values = makeIncreasing(n);
    reverse(values.begin(), values.end());
    return values;
}

vector<long long> makeAlternating(int n) {
    vector<long long> values(n);
    long long low = rnd.next(-100, -20);
    long long high = rnd.next(20, 100);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            values[i] = low + rnd.next(-5, 5);
        } else {
            values[i] = high + rnd.next(-5, 5);
        }
    }
    return values;
}

vector<long long> makePlateaus(int n) {
    vector<long long> values;
    while ((int)values.size() < n) {
        long long value = rnd.next(-30, 30);
        int count = rnd.next(1, min(5, n - (int)values.size()));
        for (int i = 0; i < count; ++i) {
            values.push_back(value);
        }
    }
    return values;
}

vector<long long> makeBoundaryValues(int n) {
    vector<long long> pool = {
        -1000000000LL, -999999999LL, -1LL, 0LL, 1LL,
        999999999LL, 1000000000LL,
    };
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 2) == 0) {
            values[i] = rnd.any(pool);
        } else {
            values[i] = rnd.next(-1000000000LL, 1000000000LL);
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    int l;
    if (mode == 0) {
        l = 1;
    } else if (mode == 1) {
        l = n;
    } else {
        l = rnd.next(1, n);
    }

    vector<long long> values;
    if (mode == 0) {
        values = makeBoundaryValues(n);
    } else if (mode == 1) {
        values = makeDecreasing(n);
    } else if (mode == 2) {
        values = makeIncreasing(n);
    } else if (mode == 3) {
        values = makeAlternating(n);
    } else if (mode == 4) {
        values = makePlateaus(n);
    } else {
        values.resize(n);
        int lo = rnd.next(-1000, 0);
        int hi = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.next(lo, hi);
        }
    }

    println(n, l);
    println(values);

    return 0;
}
