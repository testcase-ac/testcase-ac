#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_X = 1;
    const long long MAX_X = 1000000000LL;

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 12);
    vector<long long> x(n);

    if (mode == 0) {
        n = 2;
        x.assign(n, 0);
        x[0] = rnd.next(MIN_X, 20LL);
        x[1] = rnd.next(MIN_X, 20LL);
    } else if (mode == 1) {
        long long dominant = rnd.next(1000LL, MAX_X);
        x[0] = dominant;
        for (int i = 1; i < n; ++i) x[i] = rnd.next(MIN_X, 40LL);
    } else if (mode == 2) {
        long long value = rnd.next(MIN_X, 1000000LL);
        fill(x.begin(), x.end(), value);
        int tweaks = rnd.next(0, n / 2);
        for (int i = 0; i < tweaks; ++i) x[rnd.next(0, n - 1)] = rnd.next(MIN_X, 1000000LL);
    } else if (mode == 3) {
        for (long long& v : x) v = rnd.next(MAX_X - 1000, MAX_X);
    } else if (mode == 4) {
        vector<long long> anchors = {MIN_X, 2, 3, 999999999LL, MAX_X};
        for (long long& v : x) v = rnd.any(anchors);
    } else if (mode == 5) {
        long long low = rnd.next(MIN_X, 30LL);
        long long high = rnd.next(1000000LL, MAX_X);
        for (int i = 0; i < n; ++i) x[i] = (i % 2 == 0) ? high : low;
    } else {
        n = rnd.next(8, 20);
        x.assign(n, 0);
        long long lo = rnd.next(MIN_X, 1000LL);
        long long hi = rnd.next(lo, min(MAX_X, lo + rnd.next(0LL, 100000LL)));
        for (long long& v : x) v = rnd.next(lo, hi);
    }

    shuffle(x.begin(), x.end());

    println(n);
    println(x);
    return 0;
}
