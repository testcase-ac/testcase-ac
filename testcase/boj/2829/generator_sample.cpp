#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(12, 30);
    } else {
        n = rnd.next(2, 10);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        int low = rnd.next(-20, 0);
        int high = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(low, high);
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            fill(a[i].begin(), a[i].end(), base);
        }
        int row = rnd.next(0, n - 2);
        int col = rnd.next(0, n - 2);
        int size = rnd.next(2, min(n - row, n - col));
        int good = rnd.next(20, 1000);
        int bad = rnd.next(-1000, -20);
        for (int k = 0; k < size; ++k) {
            a[row + k][col + k] = good;
            a[row + k][col + size - 1 - k] = bad;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(-3, 3);
            }
        }
        int row = rnd.next(0, n - 2);
        int col = rnd.next(0, n - 2);
        int size = rnd.next(2, min(n - row, n - col));
        for (int k = 0; k < size; ++k) {
            a[row + k][col + k] = rnd.next(300, 1000);
            a[row + k][col + size - 1 - k] = rnd.next(-1000, -300);
        }
    } else if (mode == 3) {
        int value = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            fill(a[i].begin(), a[i].end(), value);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j) % 2 == 0) {
                    a[i][j] = rnd.next(500, 1000);
                } else {
                    a[i][j] = rnd.next(-1000, -500);
                }
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.any(vector<int>{-1000, -1, 0, 1, 1000});
            }
        }
    } else {
        int low = rnd.next(-1000, -100);
        int high = rnd.next(100, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(low, high);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
