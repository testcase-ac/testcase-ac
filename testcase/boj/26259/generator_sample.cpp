#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shapeMode = rnd.next(0, 4);
    int n = rnd.next(2, 9);
    int m = rnd.next(2, 9);
    if (shapeMode == 1) {
        n = 2;
        m = rnd.next(2, 12);
    } else if (shapeMode == 2) {
        n = rnd.next(2, 12);
        m = 2;
    } else if (shapeMode == 3) {
        n = rnd.next(8, 14);
        m = rnd.next(8, 14);
    } else if (shapeMode == 4) {
        n = rnd.next(2, 4);
        m = rnd.next(10, 16);
    }

    vector<vector<int>> a(n, vector<int>(m));
    int valueMode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (valueMode == 0) {
                a[i][j] = rnd.next(-9, 9);
            } else if (valueMode == 1) {
                a[i][j] = rnd.next(0, 20);
            } else if (valueMode == 2) {
                a[i][j] = rnd.next(-20, 0);
            } else if (valueMode == 3) {
                a[i][j] = (i + j) % 2 == 0 ? rnd.next(5, 40) : rnd.next(-40, -5);
            } else if (valueMode == 4) {
                a[i][j] = (i == j || i + j == m - 1) ? rnd.next(50, 200) : rnd.next(-30, 30);
            } else {
                a[i][j] = rnd.any(vector<int>{-1000, -100, -1, 0, 1, 100, 1000});
            }
        }
    }

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int wallMode = rnd.next(0, 5);
    if (wallMode == 1) {
        x1 = x2 = rnd.next(0, n);
        y1 = rnd.next(0, m);
        y2 = rnd.next(0, m);
    } else if (wallMode == 2) {
        y1 = y2 = rnd.next(0, m);
        x1 = rnd.next(0, n);
        x2 = rnd.next(0, n);
    } else if (wallMode == 3) {
        x1 = x2 = rnd.next(1, n - 1);
        y1 = 0;
        y2 = m;
    } else if (wallMode == 4) {
        y1 = y2 = rnd.next(1, m - 1);
        x1 = 0;
        x2 = n;
    } else if (wallMode == 5) {
        if (rnd.next(0, 1) == 0) {
            x1 = x2 = rnd.next(0, n);
            y1 = rnd.next(0, m - 1);
            y2 = rnd.next(y1 + 1, m);
        } else {
            y1 = y2 = rnd.next(0, m);
            x1 = rnd.next(0, n - 1);
            x2 = rnd.next(x1 + 1, n);
        }
    }

    if (rnd.next(0, 1) == 1) {
        swap(x1, x2);
        swap(y1, y2);
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    println(x1, y1, x2, y2);

    return 0;
}
