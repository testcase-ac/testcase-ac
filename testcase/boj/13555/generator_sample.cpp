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
    } else if (mode == 1) {
        n = rnd.next(45, 60);
    } else {
        n = rnd.next(2, 30);
    }

    int k;
    if (mode == 1) {
        k = rnd.next(45, min(50, n));
    } else if (mode == 2) {
        k = n;
    } else if (mode == 3) {
        k = 1;
    } else {
        k = rnd.next(1, min(50, n));
    }

    vector<int> a(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 5);
    } else if (mode == 1) {
        int start = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) a[i] = start + i;
    } else if (mode == 2) {
        int cur = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 3);
            a[i] = max(1, cur);
        }
    } else if (mode == 3) {
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, alphabet);
    } else if (mode == 4) {
        int low = rnd.next(1, 20);
        int high = rnd.next(99980, 100000);
        for (int i = 0; i < n; ++i) a[i] = (rnd.next(0, 1) ? high - rnd.next(0, 20) : low + rnd.next(0, 20));
    } else if (mode == 5) {
        int value = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) a[i] = value;
    } else {
        int base = rnd.next(1, 99950);
        for (int i = 0; i < n; ++i) {
            int block = i / rnd.next(2, 5);
            a[i] = min(100000, base + block + rnd.next(0, 2));
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    }

    println(n, k);
    println(a);

    return 0;
}
