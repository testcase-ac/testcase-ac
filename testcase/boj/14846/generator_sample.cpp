#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 15) {
        n = 1;
    } else {
        n = rnd.next(2, 18);
    }

    int valueLimit = rnd.next(1, 10);
    int pattern = rnd.next(5);
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value;
            if (pattern == 0) {
                value = rnd.next(1, valueLimit);
            } else if (pattern == 1) {
                value = i % valueLimit + 1;
            } else if (pattern == 2) {
                value = j % valueLimit + 1;
            } else if (pattern == 3) {
                value = (i + j) % valueLimit + 1;
            } else {
                value = (i == j || i + j == n - 1) ? valueLimit : rnd.next(1, valueLimit);
            }
            a[i][j] = value;
        }
    }

    int q = rnd.next(1, 80);
    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    println(q);

    for (int query = 0; query < q; ++query) {
        int x1 = rnd.next(1, n);
        int y1 = rnd.next(1, n);
        int x2 = rnd.next(x1, n);
        int y2 = rnd.next(y1, n);

        int shape = rnd.next(6);
        if (shape == 0) {
            x2 = x1;
            y2 = y1;
        } else if (shape == 1) {
            x1 = 1;
            y1 = 1;
            x2 = n;
            y2 = n;
        } else if (shape == 2) {
            x2 = x1;
        } else if (shape == 3) {
            y2 = y1;
        } else if (shape == 4) {
            x1 = rnd.next(1, n);
            x2 = rnd.next(x1, min(n, x1 + 2));
            y1 = rnd.next(1, n);
            y2 = rnd.next(y1, min(n, y1 + 2));
        }

        println(x1, y1, x2, y2);
    }

    return 0;
}
