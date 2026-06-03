#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_Y = -1000000000;
const int MAX_Y = 1000000000;

int bounded(long long x) {
    return (int)min<long long>(MAX_Y, max<long long>(MIN_Y, x));
}

int smallValue(int scale) {
    return rnd.next(-scale, scale);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    vector<int> y(n, 0);

    if (mode == 0) {
        int value = rnd.next(0, 4) == 0 ? rnd.any(vector<int>{MIN_Y, MAX_Y}) : smallValue(20);
        fill(y.begin(), y.end(), value);
    } else if (mode == 1) {
        int a = rnd.next(1, 100000);
        int shift = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            int phase = (i + shift) % 4;
            if (phase == 1) y[i] = a;
            if (phase == 3) y[i] = -a;
        }
    } else if (mode == 2) {
        int spikes = rnd.next(1, min(n, 8));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, n - 1);
            y[pos] = rnd.next(0, 3) == 0 ? rnd.any(vector<int>{MIN_Y, MAX_Y}) : smallValue(1000000);
        }
    } else if (mode == 3) {
        long long cur = smallValue(50);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-step, step);
            y[i] = bounded(cur);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 5);
            if (bucket == 0) y[i] = MIN_Y;
            else if (bucket == 1) y[i] = MAX_Y;
            else y[i] = smallValue(1000);
        }
    } else {
        int lo = rnd.next(-1000000, 0);
        int hi = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) y[i] = rnd.next(lo, hi);
    }

    println(n);
    println(y);

    return 0;
}
