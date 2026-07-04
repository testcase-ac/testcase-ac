#include "testlib.h"

#include <vector>

using namespace std;

vector<vector<int>> makeMatrix(int n, int mode) {
    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = value;
    } else if (mode == 1) {
        int offset = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = (i + j + offset) % 2;
    } else if (mode == 2) {
        bool rows = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = rows ? (i % 2) : (j % 2);
    } else if (mode == 3) {
        int borderValue = rnd.next(0, 1);
        int innerValue = 1 - borderValue;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool border = i == 0 || j == 0 || i == n - 1 || j == n - 1;
                a[i][j] = border ? borderValue : innerValue;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i][i] = 1;
            if (rnd.next(0, 1))
                a[i][n - 1 - i] = 1;
        }
    } else if (mode == 5) {
        int ones = rnd.next(0, n * n);
        vector<int> cells(n * n);
        for (int i = 0; i < n * n; ++i)
            cells[i] = i;
        shuffle(cells.begin(), cells.end());
        for (int idx = 0; idx < ones; ++idx)
            a[cells[idx] / n][cells[idx] % n] = 1;
    } else {
        int p = rnd.next(10, 90);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = rnd.next(1, 100) <= p;
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 7);
    vector<int> sizes = {1, 2, 3, 4, 5, rnd.next(6, 12), rnd.next(13, 20)};
    shuffle(sizes.begin(), sizes.end());

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = sizes[tc % (int)sizes.size()];
        if (tc >= (int)sizes.size())
            n = rnd.next(1, 20);

        int kMode = rnd.next(0, 4);
        int k;
        if (kMode == 0)
            k = 0;
        else if (kMode == 1)
            k = 1;
        else if (kMode == 2)
            k = rnd.next(2, 10);
        else if (kMode == 3)
            k = rnd.next(11, 60);
        else
            k = rnd.next(250, 300);

        println(n, k);
        vector<vector<int>> a = makeMatrix(n, rnd.next(0, 6));
        for (int i = 0; i < n; ++i)
            println(a[i]);
    }

    return 0;
}
