#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(8, 16);
    } else {
        n = rnd.next(2, 12);
    }

    int a;
    int b;
    if (mode == 0) {
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    } else if (mode == 1) {
        a = rnd.next(0, min(n, 2));
        b = rnd.next(max(0, n - 3), n);
    } else if (mode == 2) {
        a = n;
        b = rnd.next(0, n);
    } else if (mode == 3) {
        a = rnd.next(0, n);
        b = 0;
    } else if (mode == 4) {
        a = rnd.next(0, n / 2);
        b = rnd.next(n / 2, n);
    } else {
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    }

    println(n);
    println(a, b);

    for (int i = 0; i < n; ++i) {
        int r;
        int s;
        int p;
        int q;

        if (mode == 0) {
            r = rnd.next(1, 8);
            s = rnd.next(r, min(100, r + 3));
            p = rnd.next(1, r);
            q = rnd.next(1, r);
        } else if (mode == 1) {
            r = rnd.next(70, 100);
            s = rnd.next(r, 100);
            p = rnd.next(1, min(r, 12));
            q = rnd.next(1, min(r, 12));
        } else if (mode == 2) {
            r = rnd.next(1, 100);
            s = 100;
            p = rnd.next(1, r);
            q = rnd.next(1, r);
        } else if (mode == 3) {
            r = rnd.next(1, 25);
            s = rnd.next(r, min(100, r + 5));
            p = r;
            q = r;
        } else if (mode == 4) {
            r = rnd.next(40, 90);
            s = rnd.next(r, 100);
            p = rnd.next(max(1, r - 5), r);
            q = rnd.next(1, r);
        } else if (mode == 5) {
            r = rnd.next(1, 100);
            s = r;
            p = rnd.next(1, r);
            q = rnd.next(1, r);
        } else {
            r = rnd.next(1, 100);
            s = rnd.next(r, 100);
            p = rnd.next(1, r);
            q = rnd.next(1, r);
        }

        if (rnd.next(0, 4) == 0) {
            swap(p, q);
        }

        println(p, q, r, s);
    }

    return 0;
}
