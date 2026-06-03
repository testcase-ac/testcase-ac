#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 15);
    int m = rnd.next(1, min(60, n * n * 3));
    int mode = rnd.next(0, 3);

    vector<vector<int>> t(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }

            if (mode == 0) {
                t[i][j] = rnd.next(1, 20);
            } else if (mode == 1) {
                int base = abs(i - j) + 1;
                t[i][j] = rnd.next(base, base + 8);
            } else if (mode == 2) {
                t[i][j] = (rnd.next(0, 4) == 0 ? rnd.next(50, 200) : rnd.next(1, 12));
            } else {
                t[i][j] = rnd.next(1, 1000000);
            }
        }
    }

    vector<vector<int>> dist = t;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(t[i]);
    }

    for (int q = 0; q < m; ++q) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        int d = dist[a - 1][b - 1];
        int c;

        if (d == 0) {
            c = rnd.next(1, 10);
        } else {
            int choice = rnd.next(0, 5);
            if (choice == 0) {
                c = max(1, d - rnd.next(1, min(d, 10)));
            } else if (choice == 1) {
                c = d;
            } else if (choice == 2) {
                c = min(1000000000, d + rnd.next(1, 20));
            } else if (choice == 3) {
                c = rnd.next(1, 100);
            } else {
                c = rnd.next(1, 1000000000);
            }
        }

        println(a, b, c);
    }

    return 0;
}
