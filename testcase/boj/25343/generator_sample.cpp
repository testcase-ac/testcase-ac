#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(1, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 && rnd.next(0, 3) == 0) ? 1 : rnd.next(2, 12);
    vector<vector<int>> a(n, vector<int>(n));

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            fill(a[i].begin(), a[i].end(), value);
        }
    } else if (mode == 1) {
        int start = rnd.next(1, 200);
        int rowStep = rnd.next(0, 20);
        int colStep = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = clampValue(start + i * rowStep + j * colStep + rnd.next(0, 3));
            }
        }
    } else if (mode == 2) {
        int high = rnd.next(500, 10000);
        int rowStep = rnd.next(0, 25);
        int colStep = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = clampValue(high - i * rowStep - j * colStep + rnd.next(-2, 2));
            }
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 9500);
        int span = rnd.next(1, min(500, 10000 - lo));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(lo, lo + span);
            }
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 200);
        int bend = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int onPath = (i <= bend && j == 0) || (i == bend) || (i >= bend && j == n - 1);
                int progress = i + j + 1;
                a[i][j] = clampValue(base + (onPath ? progress * rnd.next(2, 7) : rnd.next(0, n)));
            }
        }
    } else {
        int lowValue = rnd.next(1, 20);
        int highValue = rnd.next(9000, 10000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j + rnd.next(0, 1)) % 2 == 0) {
                    a[i][j] = lowValue + rnd.next(0, 5);
                } else {
                    a[i][j] = highValue - rnd.next(0, 5);
                }
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
