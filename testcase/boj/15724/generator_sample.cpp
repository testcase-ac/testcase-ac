#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(2, 30);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 4) {
        n = rnd.next(6, 18);
        m = rnd.next(6, 18);
    } else {
        n = rnd.next(2, 25);
        m = rnd.next(2, 25);
    }

    vector<vector<int>> a(n, vector<int>(m));
    int valueMode = rnd.next(0, 4);
    int base = rnd.next(1, 100);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (valueMode == 0) {
                a[i][j] = base;
            } else if (valueMode == 1) {
                a[i][j] = 1 + (i + j) % 100;
            } else if (valueMode == 2) {
                a[i][j] = ((i + j) % 2 == 0 ? 1 : 100);
            } else if (valueMode == 3) {
                a[i][j] = min(100, 1 + i * m + j);
            } else {
                a[i][j] = rnd.next(1, 100);
            }
        }
    }

    int k;
    if (n * m == 1) {
        k = rnd.next(1, 6);
    } else if (mode <= 2) {
        k = rnd.next(4, 18);
    } else {
        k = rnd.next(8, 40);
    }

    vector<vector<int>> queries;
    queries.push_back({1, 1, n, m});
    queries.push_back({1, 1, 1, 1});
    queries.push_back({n, m, n, m});
    if (n > 1) {
        int x1 = rnd.next(1, n);
        int x2 = rnd.next(1, n);
        if (x1 > x2) swap(x1, x2);
        queries.push_back({x1, 1, x2, m});
    }
    if (m > 1) {
        int y1 = rnd.next(1, m);
        int y2 = rnd.next(1, m);
        if (y1 > y2) swap(y1, y2);
        queries.push_back({1, y1, n, y2});
    }

    while ((int)queries.size() < k) {
        int x1 = rnd.next(1, n);
        int x2 = rnd.next(1, n);
        int y1 = rnd.next(1, m);
        int y2 = rnd.next(1, m);
        if (rnd.next(0, 4) == 0) x2 = x1;
        if (rnd.next(0, 4) == 0) y2 = y1;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        queries.push_back({x1, y1, x2, y2});
    }

    shuffle(queries.begin(), queries.end());

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    println(k);
    for (int i = 0; i < k; ++i) {
        println(queries[i][0], queries[i][1], queries[i][2], queries[i][3]);
    }

    return 0;
}
