#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    vector<int> d;

    if (mode == 0) {
        n = rnd.next(3, 12);
        d.resize(n);
        int maxValue = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) d[i] = rnd.next(0, maxValue);
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        d.resize(n);
        for (int i = 0; i < n; ++i) d[i] = i % 3;
        if (rnd.next(2)) reverse(d.begin(), d.end());
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        d.resize(n);
        for (int i = 0; i < n; ++i) d[i] = (i % 2 == 0 ? rnd.next(0, 1) : rnd.next(1, 2));
        shuffle(d.begin(), d.end());
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        d.resize(n);
        int special = rnd.next(n);
        for (int i = 0; i < n; ++i) d[i] = rnd.next(0, 2);
        d[special] = n;
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        d.assign(n, rnd.next(0, 2));
        int changes = rnd.next(1, min(n, 6));
        for (int i = 0; i < changes; ++i) d[rnd.next(n)] = rnd.next(0, n);
    } else if (mode == 5) {
        n = rnd.next(3, 40);
        d.resize(n);
        int lo = rnd.next(0, n / 2);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) d[i] = rnd.next(lo, hi);
    } else if (mode == 6) {
        n = rnd.next(30, 120);
        d.resize(n);
        int period = rnd.next(2, 7);
        for (int i = 0; i < n; ++i) d[i] = i % period;
    } else {
        n = rnd.next(3, 30);
        d.resize(n);
        int left = 0;
        int right = n - 1;
        int value = 0;
        while (left <= right) {
            d[left++] = value;
            if (left <= right) d[right--] = min(n, value + rnd.next(0, 2));
            value = min(n, value + rnd.next(0, 2));
        }
    }

    println(n);
    println(d);
    return 0;
}
