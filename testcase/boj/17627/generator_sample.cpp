#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int q;

    if (mode == 0) {
        n = 1;
        q = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        q = rnd.next(4, 12);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
        q = rnd.next(8, 18);
    } else if (mode == 3) {
        n = rnd.next(13, 25);
        q = rnd.next(12, 30);
    } else {
        n = rnd.next(2, 30);
        q = rnd.next(1, 30);
    }

    vector<int> a(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            a[i] = rnd.next(0, 15);
        } else if (valueMode == 1) {
            a[i] = 1 << rnd.next(0, 29);
        } else if (valueMode == 2) {
            a[i] = (i % 2 == 0 ? rnd.next(0, 31) : 1000000000 - rnd.next(0, 31));
        } else if (valueMode == 3) {
            a[i] = rnd.next(0, 1) ? 0 : 1000000000;
        } else {
            a[i] = rnd.next(0, 1000000000);
        }
    }

    println(n, q);
    println(a);

    for (int action = 0; action < q; ++action) {
        bool doUpdate = n > 1 && rnd.next(0, 99) < 40;
        if (mode == 0) {
            doUpdate = rnd.next(0, 99) < 50;
        }

        if (doUpdate) {
            int i = rnd.next(1, n);
            int j;
            int updateMode = rnd.next(0, 3);
            if (updateMode == 0) {
                j = 0;
            } else if (updateMode == 1) {
                j = 1000000000;
            } else if (updateMode == 2) {
                j = rnd.next(0, 63);
            } else {
                j = rnd.next(0, 1000000000);
            }
            println(1, i, j);
        } else {
            int l;
            int u;
            int queryMode = rnd.next(0, 5);
            if (queryMode == 0) {
                l = u = rnd.next(1, n);
            } else if (queryMode == 1) {
                l = 1;
                u = n;
            } else if (queryMode == 2) {
                l = rnd.next(1, n);
                int len = rnd.next(1, min(5, n - l + 1));
                u = l + len - 1;
            } else if (queryMode == 3 && n >= 2) {
                l = rnd.next(1, n - 1);
                u = l + 1;
            } else if (queryMode == 4) {
                l = rnd.next(1, n);
                int remaining = n - l + 1;
                int len = rnd.next(1, remaining);
                if (rnd.next(0, 1) && len < remaining) ++len;
                u = l + len - 1;
            } else {
                l = rnd.next(1, n);
                u = rnd.next(l, n);
            }
            println(2, l, u);
        }
    }

    return 0;
}
