#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? rnd.next(2, 4) : rnd.next(3, 10);
    int k = rnd.next(0, n - 1);
    vector<vector<int>> t(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) t[i][j] = rnd.next(0, 12);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) t[i][j] = rnd.next(1, 1000);
            }
        }
    } else if (mode == 2) {
        int hub = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (i == hub || j == hub) {
                    t[i][j] = rnd.next(0, 9);
                } else {
                    t[i][j] = rnd.next(40, 200);
                }
            }
        }
    } else if (mode == 3) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) t[i][j] = rnd.next(80, 300);
            }
        }
        for (int i = 0; i + 1 < n; ++i) {
            t[order[i]][order[i + 1]] = rnd.next(0, 8);
            t[order[i + 1]][order[i]] = rnd.next(20, 80);
        }
    } else {
        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(0, 25);
            y[i] = rnd.next(0, 25);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
                t[i][j] = min(1000, dist * rnd.next(1, 6) + rnd.next(0, 15));
            }
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(t[i]);
    }

    return 0;
}
