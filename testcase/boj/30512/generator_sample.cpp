#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? 1 : rnd.next(2, 20);
    int q = mode == 0 ? rnd.next(1, 8) : rnd.next(1, 25);

    vector<int> a(n);
    int valueLimit = rnd.any(vector<int>{0, 1, 5, 20, 1000000});
    for (int i = 0; i < n; ++i) {
        if (mode == 1) {
            a[i] = (i % 2 == 0 ? valueLimit : rnd.next(0, valueLimit));
        } else if (mode == 2) {
            a[i] = rnd.next(0, valueLimit);
        } else {
            a[i] = rnd.next(0, 1000000);
        }
    }

    println(n);
    println(a);
    println(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        if (mode == 0) {
            l = r = 1;
        } else if (mode == 1) {
            l = 1;
            r = n;
        } else if (mode == 2) {
            l = r = rnd.next(1, n);
        } else if (mode == 3) {
            int width = max(1, n - i % n);
            l = rnd.next(1, n - width + 1);
            r = l + width - 1;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        int x;
        if (i % 5 == 0) {
            x = 0;
        } else if (i % 5 == 1) {
            x = 1000000;
        } else if (mode == 3) {
            x = rnd.next(0, 50);
        } else {
            x = rnd.next(0, 1000000);
        }
        println(l, r, x);
    }

    return 0;
}
