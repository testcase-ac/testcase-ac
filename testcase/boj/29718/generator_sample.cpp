#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, a;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 18);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        m = 1;
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(2, 18);
    }

    if (mode == 2) {
        a = 1;
    } else if (mode == 3) {
        a = m;
    } else {
        a = rnd.next(1, m);
    }

    vector<vector<int>> q(n, vector<int>(m));

    if (mode == 4) {
        int center = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int dist = abs(j - center);
                int hi = max(1, 500 - dist * rnd.next(20, 80));
                q[i][j] = rnd.next(max(1, hi - 80), hi);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                q[i][j] = ((i + j) % 2 == 0) ? rnd.next(450, 500) : rnd.next(1, 60);
            }
        }
    } else {
        int lo = rnd.next(1, 250);
        int hi = rnd.next(lo, 500);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                q[i][j] = rnd.next(lo, hi);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(q[i]);
    }
    println(a);

    return 0;
}
