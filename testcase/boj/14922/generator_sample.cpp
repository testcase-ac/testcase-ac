#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_A = 700000000;
    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 18);
    vector<int> a(n);

    if (mode == 0) {
        int lo = rnd.next(0, 20);
        int hi = rnd.next(lo, min(MAX_A, lo + rnd.next(0, 80)));
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int base = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) a[i] = base + i * rnd.next(0, 5);
    } else if (mode == 2) {
        int base = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) a[i] = base + (n - 1 - i) * rnd.next(0, 5);
    } else if (mode == 3) {
        for (int& x : a) x = rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 25);
    } else if (mode == 4) {
        fill(a.begin(), a.end(), rnd.next(20, 80));
        int pos = rnd.next(0, n - 2);
        int low = rnd.next(0, 10);
        a[pos] = low;
        a[pos + 1] = rnd.next(low, low + 5);
    } else if (mode == 5) {
        n = max(n, 3);
        a.assign(n, rnd.next(30, 90));
        int pos = rnd.next(0, n - 3);
        int low = rnd.next(0, 10);
        a[pos] = low;
        a[pos + 1] = rnd.next(low, low + 4);
        a[pos + 2] = rnd.next(low, low + 4);
    } else if (mode == 6) {
        int x = rnd.next(0, 30);
        int y = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? x : y);
    } else {
        int lo = rnd.next(max(0, MAX_A - 1000), MAX_A);
        for (int& x : a) x = rnd.next(lo, MAX_A);
    }

    println(n);
    println(a);
    return 0;
}
