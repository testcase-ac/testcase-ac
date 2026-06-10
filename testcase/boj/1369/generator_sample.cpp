#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int makeValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 97);
    }
    if (mode == 1) {
        return 1 << rnd.next(0, 12);
    }
    if (mode == 2) {
        int value = 1;
        int exp = rnd.next(0, 8);
        for (int i = 0; i < exp; ++i) value *= 5;
        return value;
    }
    if (mode == 3) {
        int value = 1;
        int twos = rnd.next(0, 6);
        int fives = rnd.next(0, 6);
        for (int i = 0; i < twos; ++i) value *= 2;
        for (int i = 0; i < fives; ++i) value *= 5;
        return value;
    }
    if (mode == 4) {
        vector<int> values = {10, 20, 25, 40, 50, 100, 125, 200, 250, 500,
                              625, 1000, 3125, 10000, 100000, 1000000};
        return rnd.any(values);
    }
    return rnd.next(1, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode < 4) {
        n = rnd.next(2, 5);
    } else if (sizeMode < 8) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(13, 25);
    }

    vector<vector<int>> a(n, vector<int>(n));
    int valueMode = rnd.next(0, 5);
    int zeroPercent = rnd.next(0, 45);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (rnd.next(0, 99) < zeroPercent) {
                a[i][j] = 0;
            } else {
                a[i][j] = makeValue(rnd.next(0, 99) < 70 ? valueMode : rnd.next(0, 5));
            }
        }
    }

    int row = 0;
    int col = 0;
    a[row][col] = makeValue(rnd.next(0, 99) < 65 ? valueMode : rnd.next(0, 5));
    while (row + 1 < n || col + 1 < n) {
        if (row + 1 == n) {
            ++col;
        } else if (col + 1 == n) {
            ++row;
        } else if (rnd.next(0, 1) == 0) {
            ++row;
        } else {
            ++col;
        }
        a[row][col] = makeValue(rnd.next(0, 99) < 65 ? valueMode : rnd.next(0, 5));
    }

    if (rnd.next(0, 99) < 35) {
        for (int i = 0; i < n; ++i) {
            int j = rnd.next(0, n - 1);
            if (a[i][j] != 0) a[i][j] = makeValue(rnd.next(1, 4));
        }
        for (int j = 0; j < n; ++j) {
            int i = rnd.next(0, n - 1);
            if (a[i][j] != 0) a[i][j] = makeValue(rnd.next(1, 4));
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
