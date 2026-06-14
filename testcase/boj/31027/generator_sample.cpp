#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int valueFromProfile(int profile) {
    if (profile == 0) return rnd.next(1, 9);
    if (profile == 1) return rnd.next(1, 100);
    if (profile == 2) return rnd.next(999900, 1000000);
    if (profile == 3) return rnd.next(1, 1000000);
    return rnd.next(1, 3);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 7);
        if (n % 2 == 0) ++n;
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        if (n % 2 == 1) ++n;
    } else {
        n = rnd.next(3, 20);
    }

    vector<vector<int>> a(2, vector<int>(n, 1));
    int profile = rnd.next(0, 4);
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < n; ++col) {
            a[row][col] = valueFromProfile(profile);
        }
    }

    if (mode == 1 || mode == 2) {
        int mid = n / 2;
        for (int row = 0; row < 2; ++row) {
            for (int col = max(0, mid - 1); col <= min(n - 1, mid + 1); ++col) {
                a[row][col] = rnd.next(500000, 1000000);
            }
        }
    } else if (mode == 3) {
        int heavyRow = rnd.next(0, 1);
        for (int col = 0; col < n; ++col) {
            a[heavyRow][col] = rnd.next(100000, 1000000);
            a[1 - heavyRow][col] = rnd.next(1, 20);
        }
    } else if (mode == 4) {
        for (int col = 0; col < n; ++col) {
            int leftWeight = n - col;
            int rightWeight = col + 1;
            a[0][col] = rnd.next(1, leftWeight * 100);
            a[1][col] = rnd.next(1, rightWeight * 100);
        }
    } else if (mode == 5) {
        int pivot = rnd.next(0, n - 1);
        for (int col = 0; col < n; ++col) {
            if (col <= pivot) {
                a[0][col] = rnd.next(1, 30);
                a[1][col] = rnd.next(500000, 1000000);
            } else {
                a[0][col] = rnd.next(500000, 1000000);
                a[1][col] = rnd.next(1, 30);
            }
        }
    } else if (mode == 6) {
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < n; ++col) {
                a[row][col] = (rnd.next(0, 4) == 0) ? 1000000 : rnd.next(1, 5);
            }
        }
    }

    a[0][0] = 0;
    a[1][n - 1] = 0;

    println(n);
    println(a[0]);
    println(a[1]);

    return 0;
}
