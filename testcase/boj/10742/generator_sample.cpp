#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        k = 1;
        a = {rnd.next(1, 1000000)};
    } else if (mode == 1) {
        n = rnd.next(2, 35);
        k = 1;
        int lo = rnd.next(1, 999000);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        n = rnd.next(2, 45);
        k = n;
        int lo = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) a.push_back(min(1000000, lo + i * rnd.next(1, 1000)));
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(4, 70);
        k = rnd.next(2, n);
        int low = rnd.next(1, 100);
        int high = rnd.next(999000, 1000000);
        for (int i = 0; i < n; ++i) a.push_back(low);
        int len = rnd.next(k, n);
        int start = rnd.next(0, n - len);
        for (int i = start; i < start + len; ++i) a[i] = high - rnd.next(0, 1000);
    } else if (mode == 4) {
        n = rnd.next(5, 80);
        k = rnd.next(2, n);
        int base = rnd.next(100, 1000000);
        for (int i = 0; i < n; ++i) {
            int delta = (i % 2 == 0 ? rnd.next(0, 99) : -rnd.next(0, 99));
            a.push_back(max(1, min(1000000, base + delta)));
        }
    } else if (mode == 5) {
        n = rnd.next(3, 60);
        k = rnd.next(2, n);
        int value = rnd.next(1, 1000000);
        a.assign(n, value);
        int changes = rnd.next(1, min(n, 6));
        for (int i = 0; i < changes; ++i) a[rnd.next(n)] = rnd.next(1, 1000000);
    } else if (mode == 6) {
        n = rnd.next(10, 120);
        k = rnd.next(1, n);
        int lo = rnd.next(1, 900000);
        int width = rnd.next(0, 100000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, min(1000000, lo + width)));
    } else {
        n = rnd.next(2, 90);
        k = rnd.next(1, n);
        int current = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(-5000, 5000);
            current = max(1, min(1000000, current));
            a.push_back(current);
        }
    }

    println(n, k);
    println(a);
    return 0;
}
