#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 6) {
        n = rnd.next(40, 80);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> diff(n);

    if (mode == 0) {
        fill(diff.begin(), diff.end(), 0);
    } else if (mode == 1) {
        int cur = rnd.next(-20, 20);
        int step = rnd.next(1, 250);
        for (int i = 0; i < n; ++i) {
            diff[i] = cur;
            cur += step;
            if (cur > 10000) cur = 10000;
        }
        if (rnd.next(0, 1)) reverse(diff.begin(), diff.end());
    } else if (mode == 2) {
        int positive = rnd.next(1, 10000);
        int negative = -rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            diff[i] = (i % 2 == 0) ? positive : negative;
            if (rnd.next(0, 4) == 0) diff[i] = 0;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(7, n - i));
            int value = rnd.next(-10000, 10000);
            for (int j = 0; j < len; ++j) diff[i + j] = value;
            i += len;
        }
    } else if (mode == 4) {
        int spikeCount = rnd.next(1, min(n, 8));
        for (int i = 0; i < spikeCount; ++i) {
            int at = rnd.next(0, n - 1);
            diff[at] = rnd.next(0, 1) ? rnd.next(1, 10000) : -rnd.next(1, 10000);
        }
    } else if (mode == 5) {
        int cur = rnd.next(-5000, 5000);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-1200, 1200);
            cur = max(-10000, min(10000, cur));
            diff[i] = cur;
        }
    } else {
        for (int i = 0; i < n; ++i) diff[i] = rnd.next(-10000, 10000);
    }

    vector<int> p(n), t(n);
    for (int i = 0; i < n; ++i) {
        int slack = 10000 - abs(diff[i]);
        int base = rnd.next(0, slack);
        if (diff[i] >= 0) {
            p[i] = base + diff[i];
            t[i] = base;
        } else {
            p[i] = base;
            t[i] = base - diff[i];
        }
    }

    println(n);
    println(p);
    println(t);

    return 0;
}
