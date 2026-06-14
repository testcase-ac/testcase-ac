#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int q = rnd.next(1, 50);
    int mode = rnd.next(0, 4);

    vector<int> a(n);
    if (mode == 0) {
        int value = rnd.next(1, n);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int first = rnd.next(1, n);
        int second = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? first : second);
        }
    } else if (mode == 2) {
        int i = 0;
        while (i < n) {
            int len = rnd.next(1, min(6, n - i));
            int value = rnd.next(1, n);
            for (int j = 0; j < len; ++j) {
                a[i + j] = value;
            }
            i += len;
        }
    } else if (mode == 3) {
        int alphabet = rnd.next(1, min(n, 6));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, alphabet);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }
        shuffle(a.begin(), a.end());
    }

    println(n, q);
    println(a);

    for (int qi = 1; qi <= q; ++qi) {
        bool mustQuery = qi == q;
        bool doUpdate = !mustQuery && rnd.next(0, 99) < 45;

        if (doUpdate) {
            int i = rnd.next(1, n);
            int x;
            if (rnd.next(0, 99) < 55) {
                int near = rnd.next(max(1, i - 1), min(n, i + 1));
                x = a[near - 1];
            } else {
                x = rnd.next(1, n);
            }
            a[i - 1] = x;
            println(1, i, x);
        } else {
            int l = rnd.next(1, n);
            int r;
            if (rnd.next(0, 99) < 35) {
                r = l;
            } else {
                r = rnd.next(l, n);
            }
            println(2, l, r);
        }
    }

    return 0;
}
