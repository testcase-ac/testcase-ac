#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 35);
    vector<int> a(n);

    if (mode == 0) {
        n = 1;
        a.assign(1, rnd.next(0, 100000000));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        a.assign(n, 0);
        vector<int> below(n + 1);
        for (int& x : below) x = rnd.next(0, 200);
        for (int i = 0; i < n; ++i) a[i] = below[i] + below[i + 1];
    } else if (mode == 2) {
        n = rnd.next(3, 35);
        a.assign(n, 0);
        vector<int> below(n + 1);
        int value = rnd.next(0, 30);
        for (int i = 0; i <= n; ++i) {
            value += rnd.next(-5, 8);
            below[i] = max(0, value);
        }
        for (int i = 0; i < n; ++i) a[i] = below[i] + below[i + 1];
    } else if (mode == 3) {
        n = rnd.next(2, 35);
        a.assign(n, 0);
        int small = rnd.next(0, 12);
        int large = rnd.next(60, 300);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0) ? small : large;
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(2, 35);
        a.assign(n, 0);
        int value = rnd.next(0, 1000);
        fill(a.begin(), a.end(), value);
        int tweaks = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < tweaks; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] = rnd.next(0, 1000);
        }
    } else if (mode == 5) {
        n = rnd.next(5, 60);
        a.assign(n, 0);
        int lo = rnd.next(0, 50);
        int hi = rnd.next(lo, lo + 300);
        for (int& x : a) x = rnd.next(lo, hi);
    } else {
        n = rnd.next(2, 12);
        a.assign(n, 0);
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        int spikes = rnd.next(1, n);
        for (int i = 0; i < spikes; ++i) {
            a[positions[i]] = rnd.next(99999900, 100000000);
        }
    }

    println(n);
    println(a);
    return 0;
}
