#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 16);
    } else if (mode == 1) {
        n = rnd.next(1, 16);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(2, 7);
        m = rnd.next(8, 18);
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(2, 7);
    } else {
        n = rnd.next(10, 22);
        m = rnd.next(10, 22);
    }

    vector<int> smallK = {1, 2, 3, 5, 6, 10, 25, 50};
    int kMode = rnd.next(0, 3);
    int k;
    if (kMode == 0) {
        k = rnd.any(smallK);
    } else if (kMode == 1) {
        k = rnd.next(51, 500);
    } else if (kMode == 2) {
        k = rnd.next(max(1, n * m), min(1000000, n * m * 50));
    } else {
        k = rnd.next(100000, 1000000);
    }

    int valueMode = rnd.next(0, 5);
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            if (valueMode == 0) {
                value = 1;
            } else if (valueMode == 1) {
                value = 50;
            } else if (valueMode == 2) {
                value = (i + j) % 2 ? 1 : 50;
            } else if (valueMode == 3) {
                value = rnd.next(1, 5);
            } else if (valueMode == 4) {
                value = rnd.next(46, 50);
            } else {
                value = rnd.next(1, 50);
            }
            a[i][j] = value;
        }
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
