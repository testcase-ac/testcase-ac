#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 8);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(8, 15);
    } else {
        n = rnd.next(2, 12);
    }

    vector<int> lengths(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            lengths[i] = rnd.next(1, 5);
        } else if (mode == 1) {
            lengths[i] = (i % 2 == 0) ? rnd.next(1, 8) : rnd.next(80, 100);
        } else if (mode == 2) {
            lengths[i] = rnd.next(1, 100);
        } else if (mode == 3) {
            lengths[i] = rnd.next(90, 100);
        } else {
            lengths[i] = rnd.next(1, 20);
        }
    }

    int maxEdges = min(25, n * max(1, n - 1));
    int m = rnd.next(1, maxEdges);

    vector<int> a(m), b(m), c(m);
    for (int j = 0; j < m; ++j) {
        int first;
        int second;
        if (mode == 0 || rnd.next(0, 99) < 25) {
            first = rnd.next(1, n - 1);
            second = first + 1;
        } else if (mode == 3 || rnd.next(0, 99) < 35) {
            first = rnd.next(1, n / 2);
            second = rnd.next(max(first + 1, n / 2 + 1), n);
        } else {
            first = rnd.next(1, n);
            second = rnd.next(1, n - 1);
            if (second >= first) ++second;
        }

        if (rnd.next(0, 1)) swap(first, second);
        a[j] = first;
        b[j] = second;

        if (mode == 1) {
            c[j] = rnd.next(1, 15);
        } else if (mode == 3) {
            c[j] = rnd.next(85, 100);
        } else {
            c[j] = rnd.next(1, 100);
        }
    }

    println(n, m);
    println(lengths);
    for (int j = 0; j < m; ++j) {
        println(a[j], b[j], c[j]);
    }

    return 0;
}
