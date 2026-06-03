#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, q;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 6);
        q = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        m = 1;
        q = rnd.next(1, 14);
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
        q = rnd.next(15, 30);
    } else if (mode == 3) {
        n = rnd.next(6, 10);
        m = rnd.next(2, 4);
        q = rnd.next(10, 24);
    } else if (mode == 4) {
        n = rnd.next(2, 4);
        m = rnd.next(6, 10);
        q = rnd.next(10, 24);
    } else {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        q = rnd.next(1, 24);
    }

    vector<vector<int>> a(n, vector<int>(m));
    int valueMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (valueMode == 0) {
                a[i][j] = rnd.next(1, 12);
            } else if (valueMode == 1) {
                a[i][j] = 1 + ((i * m + j + rnd.next(0, 3)) % 20);
            } else if (valueMode == 2) {
                a[i][j] = (j % 2 == 0 ? 1 : 10000);
            } else {
                a[i][j] = rnd.next(9990, 10000);
            }
        }
    }

    println(n, m, q);
    for (const auto& row : a) {
        println(row);
    }

    for (int t = 0; t < q; ++t) {
        bool doUpdate = rnd.next(0, 99) < 55;
        if (n == 1 && rnd.next(0, 99) < 35) {
            doUpdate = true;
        }

        if (doUpdate) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, m - 1);
            if (rnd.next(0, 99) < 35) {
                i = rnd.any(vector<int>{0, n - 1});
            }
            if (rnd.next(0, 99) < 35) {
                j = rnd.any(vector<int>{0, m - 1});
            }

            int k;
            int updateMode = rnd.next(0, 3);
            if (updateMode == 0) {
                k = rnd.next(1, 20);
            } else if (updateMode == 1) {
                k = rnd.any(vector<int>{1, 10000});
            } else if (updateMode == 2) {
                k = 1 + ((t + i + j) % 10000);
            } else {
                k = rnd.next(9990, 10000);
            }
            println(0, i, j, k);
        } else {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            if (rnd.next(0, 99) < 30) {
                j = i;
            } else if (rnd.next(0, 99) < 35) {
                i = rnd.any(vector<int>{0, n - 1});
                j = rnd.any(vector<int>{0, n - 1});
            }
            println(1, i, j);
        }
    }

    return 0;
}
