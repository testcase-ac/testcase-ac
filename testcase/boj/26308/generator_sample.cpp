#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode <= 1) {
        n = rnd.next(2, 8);
    } else if (mode <= 4) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    vector<int> d(n);

    if (mode == 0) {
        int root = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            d[i] = abs(i - root);
        }
    } else if (mode == 1) {
        int root = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            d[i] = i == root ? 0 : rnd.next(1, min(n - 1, 4));
        }
    } else if (mode == 2) {
        int root = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            d[i] = i == root ? 0 : rnd.next(1, n - 1);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(1, n - 1);
        }
    } else if (mode == 4) {
        int zeroCount = rnd.next(2, min(n, 5));
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < zeroCount; ++i) {
            d[order[i]] = 0;
        }
        for (int i = zeroCount; i < n; ++i) {
            d[order[i]] = rnd.next(1, n - 1);
        }
    } else if (mode == 5) {
        int root = rnd.next(0, n - 1);
        int cap = rnd.next(1, min(n - 1, 10));
        for (int i = 0; i < n; ++i) {
            d[i] = i == root ? 0 : rnd.wnext(cap + 1, 2);
            if (i != root && d[i] == 0) {
                d[i] = 1;
            }
        }
    } else {
        int root = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            d[i] = i == root ? 0 : n - 1 - rnd.wnext(n, -3);
        }
    }

    println(n);
    println(d);

    return 0;
}
