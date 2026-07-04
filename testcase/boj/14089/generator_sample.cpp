#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.any(vector<int>{1, 2, 3, 10, 1000, 1000000000});
    if (mode == 2) return rnd.next(999999900, 1000000000);
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(0, 4);
    int n;
    if (nMode == 0) {
        n = 2;
    } else if (nMode == 1) {
        n = rnd.next(3, 6);
    } else {
        n = rnd.next(7, 14);
    }

    int valueMode = rnd.next(0, 3);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 3 && i > 0 && rnd.next(0, 2) == 0) {
            a[i] = a[i - 1];
        } else {
            a[i] = pickValue(valueMode);
        }
    }

    int m = rnd.next(1, 12);

    println(n);
    println(a);
    println(m);

    for (int i = 0; i < m; ++i) {
        int p;
        int q;
        int shape = rnd.next(0, 4);

        if (shape == 0) {
            p = 1;
            q = n;
        } else if (shape == 1) {
            p = rnd.next(1, n - 1);
            q = p + 1;
        } else {
            p = rnd.next(1, n);
            do {
                q = rnd.next(1, n);
            } while (p == q);
        }

        if (rnd.next(0, 1) == 0) {
            swap(p, q);
        }

        int queryMode = rnd.next(0, 4);
        int newP;
        int newQ;
        if (queryMode == 0) {
            newP = a[p - 1];
            newQ = a[q - 1];
        } else if (queryMode == 1) {
            newP = pickValue(0);
            newQ = pickValue(0);
        } else if (queryMode == 2) {
            newP = pickValue(1);
            newQ = pickValue(1);
        } else if (queryMode == 3) {
            newP = pickValue(2);
            newQ = pickValue(0);
        } else {
            newP = pickValue(3);
            newQ = pickValue(3);
        }

        println(p, newP, q, newQ);
        a[p - 1] = newP;
        a[q - 1] = newQ;
    }

    return 0;
}
