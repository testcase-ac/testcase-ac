#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<vector<int>> a;

    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
        a.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(1, 9);
            }
        }
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            n = rnd.next(2, 4);
            m = rnd.next(8, 24);
        } else {
            n = rnd.next(8, 24);
            m = rnd.next(2, 4);
        }
        a.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(1, 9);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        int value = rnd.next(4, 6);
        a.assign(n, vector<int>(m, value));
        if (value == 5) {
            int changes = rnd.next(0, n * m / 3);
            for (int k = 0; k < changes; ++k) {
                a[rnd.next(n)][rnd.next(m)] = rnd.next(1, 9);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 12);
        vector<int> top(m), bottom(m);
        for (int j = 0; j < m; ++j) {
            top[j] = rnd.next(1, 9);
            bottom[j] = rnd.next(1, 9);
            if (rnd.next(0, 2) == 0) {
                int sum = rnd.next(2, 18);
                top[j] = rnd.next(max(1, sum - 9), min(9, sum - 1));
                bottom[j] = sum - top[j];
            }
        }
        a.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (i % 2 == 0 ? top[j] : bottom[j]);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 8);
        vector<int> left(n), right(n);
        for (int i = 0; i < n; ++i) {
            left[i] = rnd.next(1, 9);
            right[i] = rnd.next(1, 9);
            if (rnd.next(0, 2) == 0) {
                int sum = rnd.next(2, 18);
                left[i] = rnd.next(max(1, sum - 9), min(9, sum - 1));
                right[i] = sum - left[i];
            }
        }
        a.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (j % 2 == 0 ? left[i] : right[i]);
            }
        }
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        int lo = rnd.next(1, 4);
        int hi = rnd.next(6, 9);
        a.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (rnd.next(0, 1) == 0 ? rnd.next(1, lo) : rnd.next(hi, 9));
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
