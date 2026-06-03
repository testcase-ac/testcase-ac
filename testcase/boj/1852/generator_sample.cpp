#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(-10000, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> evenSizes = {2, 4, 6, 8, 10, 12, 16, 20};
    int n = rnd.any(evenSizes);

    vector<vector<int>> a(n, vector<int>(3));

    if (mode == 0) {
        int lo = rnd.next(-20, 0);
        int hi = rnd.next(0, 20);
        if (lo > hi) swap(lo, hi);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 3; ++j)
                a[i][j] = rnd.next(lo, hi);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(-30, 30);
            int step = rnd.next(-15, 15);
            for (int j = 0; j < 3; ++j)
                a[i][j] = clampValue(base + step * j + rnd.next(-3, 3));
        }
    } else if (mode == 2) {
        int start = rnd.next(-100, 100);
        int rowStep = rnd.next(-25, 25);
        int colStep = rnd.next(-25, 25);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 3; ++j)
                a[i][j] = clampValue(start + rowStep * i + colStep * j);
    } else if (mode == 3) {
        vector<int> pool = {-10000, -9999, -100, -1, 0, 1, 100, 9999, 10000};
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 3; ++j)
                a[i][j] = rnd.any(pool);
    } else if (mode == 4) {
        int x = rnd.next(-10000, 10000);
        int y = rnd.next(-10000, 10000);
        int z = rnd.next(-10000, 10000);
        for (int i = 0; i < n; ++i) {
            a[i][0] = (i % 2 == 0 ? x : y);
            a[i][1] = (i % 2 == 0 ? y : z);
            a[i][2] = (i % 2 == 0 ? z : x);
        }
    } else {
        int center = rnd.next(-500, 500);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 3; ++j) {
                int sign = ((i + j) % 2 == 0 ? 1 : -1);
                a[i][j] = clampValue(center + sign * rnd.next(0, 10000));
            }
    }

    println(n);
    for (int i = 0; i < n; ++i)
        println(a[i][0], a[i][1], a[i][2]);

    return 0;
}
