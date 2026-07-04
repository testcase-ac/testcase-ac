#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(3, 30);
    vector<int> a(n);

    if (mode == 0) {
        int hi = rnd.next(1, n);
        for (int& x : a) x = rnd.next(1, hi);
    } else if (mode == 1) {
        int lo = rnd.next(1, n);
        for (int& x : a) x = rnd.next(lo, n);
    } else if (mode == 2) {
        for (int& x : a) x = rnd.next(1, n);
        sort(a.begin(), a.end());
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        int v1 = rnd.next(1, n);
        int v2 = rnd.next(1, n);
        int v3 = rnd.next(1, n);
        for (int& x : a) {
            int pick = rnd.next(0, 2);
            x = pick == 0 ? v1 : (pick == 1 ? v2 : v3);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next() < 0.35 ? rnd.next(max(1, n - 2), n) : rnd.next(1, min(n, 3));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        n = rnd.next(3, 8);
        a.assign(n, rnd.next(1, n));
        int changes = rnd.next(1, n);
        for (int i = 0; i < changes; ++i) a[rnd.next(0, n - 1)] = rnd.next(1, n);
    } else {
        for (int i = 0; i < n; ++i) {
            int center = (i % 3) + 1;
            a[i] = min(n, max(1, center + rnd.next(-1, 2)));
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
