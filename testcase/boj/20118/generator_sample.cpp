#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;
    if (mode == 0) {
        n = 2;
        m = 2;
    } else if (mode == 1) {
        n = 2;
        m = rnd.next(2, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        m = 2;
    } else if (mode == 3) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        m = rnd.next(8, 20);
    } else if (mode == 5) {
        n = rnd.next(2, 7) * 2;
        m = rnd.next(2, 7) * 2 + 1;
    } else {
        n = rnd.next(2, 13);
        m = rnd.next(2, 13);
    }

    vector<vector<int>> a(n, vector<int>(m));
    int valueMode = rnd.next(0, 5);
    int base = rnd.next(1, 1000000000);
    int low = rnd.next(1, 50);
    int high = rnd.next(999999950, 1000000000);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (valueMode == 0) {
                a[i][j] = base;
            } else if (valueMode == 1) {
                a[i][j] = ((i + j) % 2 == 0 ? low : high);
            } else if (valueMode == 2) {
                a[i][j] = rnd.next(1, 32);
            } else if (valueMode == 3) {
                a[i][j] = rnd.next(999999000, 1000000000);
            } else if (valueMode == 4) {
                int bit = rnd.next(0, 29);
                a[i][j] = 1 << bit;
            } else {
                a[i][j] = rnd.next(1, 1000000000);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
