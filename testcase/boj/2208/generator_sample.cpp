#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, n);
        a.resize(n);
        for (int& x : a) x = rnd.next(-5, 5);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = n;
        a.resize(n);
        for (int& x : a) x = rnd.next(-2000, 2000);
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        m = rnd.next(1, n);
        a.resize(n);
        for (int& x : a) x = -rnd.next(1, 30);
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        m = rnd.next(2, min(n, 10));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % m == m - 1) {
                a[i] = rnd.next(1, 25);
            } else {
                a[i] = rnd.next(-20, 8);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(8, 40);
        m = rnd.next(1, n);
        a.resize(n);
        for (int& x : a) x = rnd.any(vector<int>{-2000, -1000, -1, 0, 1, 1000, 2000});
    } else if (mode == 5) {
        n = rnd.next(10, 45);
        m = rnd.next(2, min(n, 12));
        a.resize(n);
        int left = rnd.next(0, n - m);
        int len = rnd.next(m, n - left);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(-15, -1);
        for (int i = left; i < left + len; ++i) a[i] = rnd.next(0, 20);
    } else {
        n = rnd.next(20, 60);
        m = rnd.next(1, n);
        a.resize(n);
        int lo = rnd.next(-50, 0);
        int hi = rnd.next(0, 50);
        for (int& x : a) x = rnd.next(lo, hi);
    }

    println(n, m);
    for (int x : a) println(x);

    return 0;
}
