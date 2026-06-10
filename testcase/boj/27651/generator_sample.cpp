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
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, lo + rnd.next(0, 12));
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int head = rnd.next(1, 5);
        int body = rnd.next(head + 1, head + 30);
        int tail = rnd.next(head + 1, body);
        int p = rnd.next(1, n - 2);
        int q = rnd.next(p + 1, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i < p) a[i] = rnd.next(1, head);
            else if (i < q) a[i] = rnd.next(body / 2, body);
            else a[i] = rnd.next(1, tail);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int base = (i % 2 == 0 ? rnd.next(1, 4) : rnd.next(4, 20));
            a[i] = base;
        }
    } else if (mode == 3) {
        for (int& x : a) x = rnd.next(1, 6);
        int spikes = rnd.next(1, min(5, n));
        for (int i = 0; i < spikes; ++i) a[rnd.next(0, n - 1)] = rnd.next(50, 200);
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        a.assign(n, 1);
        for (int& x : a) {
            if (rnd.next(0, 3) == 0) x = rnd.next(99980, 100000);
            else x = rnd.next(1, 20);
        }
    } else if (mode == 5) {
        int cur = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-2, 4);
            cur = max(1, min(cur, 40));
            a[i] = cur;
        }
    } else {
        n = rnd.next(3, 8);
        a.assign(n, rnd.next(1, 3));
        int pos = rnd.next(1, n - 2);
        a[pos] = rnd.next(10, 80);
    }

    println(n);
    println(a);

    return 0;
}
