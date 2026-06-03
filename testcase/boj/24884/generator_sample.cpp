#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 6);
    int t = rnd.next(1, 11);
    int k = rnd.next(1, n);
    int w = rnd.next(0, n - 1);
    vector<int> f(n);

    if (mode == 0) {
        n = 1;
        w = 0;
        t = rnd.next(1, 11);
        k = 1;
        f[0] = rnd.any(vector<int>{0, 1, 2, 3, 50, rnd.next(0, 50)});
    } else if (mode == 1) {
        n = 6;
        w = rnd.any(vector<int>{0, 5, rnd.next(0, 5)});
        t = 11;
        k = rnd.any(vector<int>{1, 3, 6});
        f.assign(n, 0);
        for (int i = 0; i < n; ++i) f[i] = rnd.next(0, 6);
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        w = rnd.next(0, n - 1);
        t = rnd.next(8, 11);
        k = n;
        f.assign(n, 0);
        for (int i = 0; i < n; ++i) f[i] = rnd.next(1, 8);
    } else if (mode == 3) {
        n = rnd.next(2, 6);
        w = rnd.next(0, n - 1);
        t = rnd.next(1, 11);
        k = rnd.next(1, n);
        int lo = rnd.next(35, 50);
        for (int i = 0; i < n; ++i) f[i] = rnd.next(lo, 50);
    } else if (mode == 4) {
        n = rnd.next(2, 6);
        w = rnd.any(vector<int>{0, n - 1, rnd.next(0, n - 1)});
        t = rnd.next(2, 11);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            f[i] = (i % 2 == 0 ? rnd.next(0, 3) : rnd.next(20, 50));
        }
    } else if (mode == 5) {
        n = rnd.next(3, 6);
        w = rnd.next(0, n - 1);
        t = rnd.next(1, 11);
        k = rnd.any(vector<int>{1, n, rnd.next(1, n)});
        int base = rnd.next(0, 50);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3);
            f[i] = max(0, min(50, base + delta));
        }
    } else {
        n = rnd.next(1, 6);
        w = rnd.next(0, n - 1);
        t = rnd.next(1, 11);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) f[i] = rnd.next(0, 50);
    }

    println(n, w, t, k);
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ' ';
        cout << f[i];
    }
    cout << '\n';

    return 0;
}
