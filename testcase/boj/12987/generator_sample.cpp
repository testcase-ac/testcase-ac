#include "testlib.h"

#include <vector>
using namespace std;

const int MIN_A = -10000;
const int MAX_A = 10000;

int signedValue(int limit) {
    int value = rnd.next(0, limit);
    if (rnd.next(0, 1) == 0) value = -value;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    int m;
    vector<vector<int>> a;

    if (mode == 0) {
        n = 1;
        k = rnd.any(vector<int>{1, 2, 3, 1000000000});
        m = rnd.any(vector<int>{1, 2, 7, 10000});
        a.assign(n, vector<int>(n, rnd.any(vector<int>{MIN_A, -1, 0, 1, MAX_A})));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.any(vector<int>{1, 2, 5, 31, 1000000000});
        m = rnd.next(2, 10000);
        a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            a[i][i] = signedValue(rnd.next(1, 10000));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 7);
        k = rnd.next(1, 12);
        m = rnd.next(2, 30);
        a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            a[i][i] = rnd.next(0, 1);
            if (i + 1 < n) a[i][i + 1] = signedValue(3);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 9);
        k = rnd.any(vector<int>{2, 3, 10, 999999937});
        m = rnd.any(vector<int>{1, 2, 9999, 10000});
        a.assign(n, vector<int>(n, 0));
        int nonzero = rnd.next(n, n * n);
        for (int t = 0; t < nonzero; ++t) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            a[r][c] = rnd.any(vector<int>{MIN_A, -100, -1, 1, 100, MAX_A});
        }
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        k = rnd.next(1, 1000000000);
        m = rnd.next(2, 10000);
        int limit = rnd.next(1, 20);
        a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = signedValue(limit);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(4, 12);
        k = rnd.any(vector<int>{50, 12345, 1000000000});
        m = rnd.any(vector<int>{2, 3, 97, 10000});
        a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            a[i][j] = rnd.any(vector<int>{-2, -1, 1, 2});
            if (rnd.next(0, 2) == 0) a[i][i] = signedValue(5);
        }
    } else {
        n = rnd.next(8, 18);
        k = rnd.next(1, 1000000000);
        m = rnd.next(1, 10000);
        a.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(0, 3) == 0) {
                    a[i][j] = signedValue(10000);
                }
            }
        }
    }

    println(n, k, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
