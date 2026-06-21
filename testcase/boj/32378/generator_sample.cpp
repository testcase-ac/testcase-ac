#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 24);
    int k = rnd.next(0, n);
    int s = rnd.next(1, 100);
    vector<int> a(n);

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = 0;
        s = rnd.next(1, 12);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-s - 5, 20);
        }
    } else if (mode == 1) {
        n = rnd.next(6, 20);
        k = rnd.next(1, min(n, 5));
        s = rnd.next(1, 30);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(-500, -1) : rnd.next(1, 500);
        }
    } else if (mode == 2) {
        n = rnd.next(20, 80);
        k = rnd.next(min(n, 35), n);
        s = rnd.next(50, 100);
        a.assign(n, rnd.next(300, 500));
    } else if (mode == 3) {
        n = rnd.next(1, 12);
        k = n;
        s = rnd.next(1, 100);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-500, 500);
        }
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        k = rnd.next(1, n - 1);
        s = rnd.next(1, 15);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i < n / 3) {
                a[i] = rnd.next(-500, -100);
            } else if (i < 2 * n / 3) {
                a[i] = rnd.next(-20, 20);
            } else {
                a[i] = rnd.next(100, 500);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(15, 60);
        k = rnd.next(1, min(n, 20));
        s = rnd.next(1, 100);
        a.assign(n, 0);
        int lo = rnd.next(-500, 0);
        int hi = rnd.next(0, 500);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (mode == 6) {
        n = rnd.next(1, 30);
        k = rnd.next(0, n);
        s = rnd.next(1, 100);
        int value = rnd.any(vector<int>{-500, -1, 0, 1, 500});
        a.assign(n, value);
    } else {
        n = rnd.next(100, 300);
        k = rnd.next(0, n);
        s = rnd.next(1, 100);
        a.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) a[i] = rnd.next(-500, -300);
            if (bucket == 1) a[i] = rnd.next(-30, 30);
            if (bucket == 2) a[i] = rnd.next(300, 500);
            if (bucket == 3) a[i] = rnd.next(-500, 500);
        }
    }

    if (rnd.next(0, 4) == 0) {
        shuffle(a.begin(), a.end());
    }

    println(n, k, s);
    println(a);

    return 0;
}
