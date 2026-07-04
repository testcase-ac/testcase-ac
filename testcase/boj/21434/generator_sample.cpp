#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int rows = rnd.next(2, 10);
    int cols = rnd.next(2, 10);
    vector<vector<int>> a(rows, vector<int>(cols));

    if (mode == 0) {
        int lo = rnd.next(-20, 0);
        int hi = rnd.next(0, 20);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(-8, 8);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = base + rnd.next(-2, 2);
            }
        }
        int r1 = rnd.next(0, rows - 2);
        int r2 = rnd.next(r1 + 1, rows - 1);
        int c1 = rnd.next(0, cols - 2);
        int c2 = rnd.next(c1 + 1, cols - 1);
        int bonus = rnd.next(10, 40);
        a[r1][c1] += bonus;
        a[r1][c2] += bonus;
        a[r2][c1] += bonus;
        a[r2][c2] += bonus;
    } else if (mode == 2) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = -rnd.next(1, 50);
            }
        }
        int r1 = rnd.next(0, rows - 2);
        int r2 = rnd.next(r1 + 1, rows - 1);
        int c1 = rnd.next(0, cols - 2);
        int c2 = rnd.next(c1 + 1, cols - 1);
        a[r1][c1] = rnd.next(-3, 3);
        a[r1][c2] = rnd.next(-3, 3);
        a[r2][c1] = rnd.next(-3, 3);
        a[r2][c2] = rnd.next(-3, 3);
    } else if (mode == 3) {
        vector<int> rowWeight(rows), colWeight(cols);
        for (int i = 0; i < rows; ++i) {
            rowWeight[i] = rnd.next(-15, 15);
        }
        for (int j = 0; j < cols; ++j) {
            colWeight[j] = rnd.next(-15, 15);
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = rowWeight[i] + colWeight[j] + rnd.next(-3, 3);
            }
        }
    } else if (mode == 4) {
        rows = rnd.next(2, 4);
        cols = rnd.next(2, 10);
        a.assign(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = rnd.next(-100, 100);
            }
        }
    } else {
        rows = rnd.next(2, 10);
        cols = rnd.next(2, 4);
        a.assign(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                a[i][j] = rnd.next(-100, 100);
            }
        }
    }

    if (rnd.next(0, 9) == 0) {
        int value = rnd.any(vector<int>{-10000000, 10000000});
        a[rnd.next(0, rows - 1)][rnd.next(0, cols - 1)] = value;
    }

    println(rows, cols);
    for (int i = 0; i < rows; ++i) {
        println(a[i]);
    }

    return 0;
}
