#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Rect {
    int i1;
    int j1;
    int i2;
    int j2;
};

Rect randomRect(int n, int mode) {
    if (mode == 0) {
        int i = rnd.next(0, n - 1);
        int j = rnd.next(0, n - 1);
        return {i, j, i, j};
    }
    if (mode == 1) {
        int i = rnd.next(0, n - 1);
        int j1 = rnd.next(0, n - 1);
        int j2 = rnd.next(j1, n - 1);
        return {i, j1, i, j2};
    }
    if (mode == 2) {
        int i1 = rnd.next(0, n - 1);
        int i2 = rnd.next(i1, n - 1);
        int j = rnd.next(0, n - 1);
        return {i1, j, i2, j};
    }
    if (mode == 3 || n == 1) {
        return {0, 0, n - 1, n - 1};
    }

    int i1 = rnd.next(0, n - 1);
    int i2 = rnd.next(i1, n - 1);
    int j1 = rnd.next(0, n - 1);
    int j2 = rnd.next(j1, n - 1);
    return {i1, j1, i2, j2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else if (mode == 2) {
        n = rnd.next(5, 9);
    } else if (mode == 3) {
        n = rnd.next(10, 18);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(20, 35);
    }

    int updates;
    int sums;
    if (mode == 0) {
        updates = rnd.next(0, 2);
        sums = rnd.next(1, 3);
    } else if (mode == 5) {
        updates = rnd.next(12, 30);
        sums = rnd.next(8, 20);
    } else {
        updates = rnd.next(1, 12);
        sums = rnd.next(1, 10);
    }
    int m = updates + sums;

    println(n, m);
    for (int i = 0; i < n; ++i) {
        vector<int> row(n);
        for (int j = 0; j < n; ++j) {
            int valueMode = rnd.next(0, 4);
            if (valueMode == 0) {
                row[j] = 1;
            } else if (valueMode == 1) {
                row[j] = 1000000;
            } else if (valueMode == 2) {
                row[j] = i * n + j + 1;
            } else if (valueMode == 3) {
                row[j] = rnd.next(1, 20);
            } else {
                row[j] = rnd.next(1, 1000000);
            }
        }
        println(row);
    }

    for (int query = 0; query < updates; ++query) {
        Rect rect = randomRect(n, rnd.next(0, 4));
        int kMode = rnd.next(0, 3);
        int k;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = 10000;
        } else if (kMode == 2) {
            k = rnd.next(2, 25);
        } else {
            k = rnd.next(1, 10000);
        }
        println(1, rect.i1, rect.j1, rect.i2, rect.j2, k);
    }

    for (int query = 0; query < sums; ++query) {
        Rect rect = randomRect(n, rnd.next(0, 4));
        println(2, rect.i1, rect.j1, rect.i2, rect.j2);
    }

    return 0;
}
