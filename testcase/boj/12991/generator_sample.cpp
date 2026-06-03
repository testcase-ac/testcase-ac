#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<long long> makeValues(int n, int mode) {
    vector<long long> values(n);

    if (mode == 0) {
        long long x = rnd.next(1, 20);
        fill(values.begin(), values.end(), x);
    } else if (mode == 1) {
        int hi = rnd.next(1, 15);
        for (long long& x : values) x = rnd.next(1, hi);
    } else if (mode == 2) {
        long long base = rnd.next(1, 1000);
        long long step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) values[i] = base + step * i;
    } else if (mode == 3) {
        long long lo = rnd.next(1, 1000);
        long long hi = rnd.next(999000000LL, 1000000000LL);
        for (long long& x : values) x = (rnd.next(0, 3) == 0 ? hi - rnd.next(0, 1000) : lo + rnd.next(0, 1000));
    } else {
        for (long long& x : values) x = rnd.next(1LL, 1000000000LL);
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        sort(values.begin(), values.end());
    } else if (order == 1) {
        sort(values.rbegin(), values.rend());
    } else {
        shuffle(values.begin(), values.end());
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(13, 25);
    } else {
        n = rnd.next(26, 45);
    }

    long long total = 1LL * n * n;
    int kMode = rnd.next(0, 5);
    long long k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = total;
    } else if (kMode == 2) {
        k = (total + 1) / 2;
    } else if (kMode == 3) {
        k = rnd.next(1LL, min(total, 10LL));
    } else if (kMode == 4) {
        k = total - rnd.next(0LL, min(total - 1, 9LL));
    } else {
        k = rnd.next(1LL, total);
    }

    vector<long long> a = makeValues(n, rnd.next(0, 4));
    vector<long long> b = makeValues(n, rnd.next(0, 4));

    println(n, k);
    println(a);
    println(b);

    return 0;
}
