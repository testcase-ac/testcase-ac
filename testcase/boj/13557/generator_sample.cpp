#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 35);
    int pattern = rnd.next(6);
    int valueLimit = rnd.next(1, 100);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (pattern == 0) {
            a[i] = rnd.next(-valueLimit, valueLimit);
        } else if (pattern == 1) {
            a[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(1, valueLimit);
        } else if (pattern == 2) {
            a[i] = rnd.next(0, valueLimit);
        } else if (pattern == 3) {
            a[i] = -rnd.next(0, valueLimit);
        } else if (pattern == 4) {
            a[i] = (i < n / 2 ? -1 : 1) * rnd.next(1, valueLimit);
        } else {
            a[i] = rnd.any(vector<int>{-100000, -valueLimit, -1, 0, 1, valueLimit, 100000});
        }
    }

    int m = rnd.next(1, 35);
    vector<vector<int>> queries;
    queries.reserve(m);

    for (int qi = 0; qi < m; ++qi) {
        int x1, y1, x2, y2;
        int mode = rnd.next(6);

        if (mode == 0 || n == 1) {
            int p = rnd.next(1, n);
            x1 = y1 = x2 = y2 = p;
        } else if (mode == 1) {
            x1 = rnd.next(1, n);
            y1 = rnd.next(x1, n);
            x2 = rnd.next(x1, y1);
            y2 = rnd.next(y1, n);
        } else if (mode == 2) {
            x1 = rnd.next(1, n);
            x2 = rnd.next(x1, n);
            y1 = rnd.next(x2, n);
            y2 = rnd.next(y1, n);
        } else if (mode == 3) {
            x1 = 1;
            y2 = n;
            x2 = rnd.next(1, n);
            y1 = rnd.next(x2, n);
        } else if (mode == 4) {
            x1 = rnd.next(1, n);
            y1 = rnd.next(x1, n);
            x2 = rnd.next(x1, y1);
            y2 = rnd.next(y1, n);
        } else {
            int left = rnd.next(1, n);
            int right = rnd.next(left, n);
            x1 = left;
            y1 = right;
            x2 = left;
            y2 = right;
        }

        queries.push_back({x1, y1, x2, y2});
    }

    println(n);
    println(a);
    println(m);
    for (const auto& q : queries) {
        println(q);
    }

    return 0;
}
