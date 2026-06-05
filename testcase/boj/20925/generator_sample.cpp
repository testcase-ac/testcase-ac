#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int t;
    if (mode == 0) {
        n = 1;
        t = rnd.next(1, 25);
    } else {
        n = rnd.next(2, mode == 4 ? 18 : 10);
        t = rnd.next(1, 80);
    }

    vector<int> c(n), e(n);
    vector<vector<int>> travel(n, vector<int>(n, 0));

    if (mode == 0) {
        c[0] = 0;
        e[0] = rnd.next(0, 200);
    } else if (mode == 1) {
        int rate = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            c[i] = i == 0 ? 0 : rnd.next(0, min(1000000, i * rate * 3));
            e[i] = rate + rnd.next(0, 12) + i * rnd.next(0, 8);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = abs(i - j);
                travel[i][j] = travel[j][i] = rnd.next(dist, min(1000, dist + 5));
            }
        }
    } else if (mode == 2) {
        int zeroCount = rnd.next(1, min(n, 3));
        for (int i = 0; i < n; ++i) {
            c[i] = i < zeroCount ? 0 : rnd.next(1, 250);
            e[i] = rnd.next(0, 120);
        }
        shuffle(c.begin(), c.end());
        shuffle(e.begin(), e.end());
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool sameCluster = (i < n / 2) == (j < n / 2);
                int lo = sameCluster ? 1 : max(1, t / 2);
                int hi = sameCluster ? min(20, max(1, t)) : min(1000, max(lo, t + 20));
                travel[i][j] = travel[j][i] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            c[i] = i == 0 ? 0 : rnd.next(0, 1000);
            e[i] = rnd.next(0, 1000);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                travel[i][j] = travel[j][i] = rnd.next(1, 1000);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            c[i] = i == 0 ? 0 : rnd.next(0, 1000000);
            e[i] = rnd.next(0, 1000000);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                travel[i][j] = travel[j][i] = rnd.next(1, min(1000, max(1, t * 2)));
            }
        }
    }

    println(n, t);
    for (int i = 0; i < n; ++i) {
        println(c[i], e[i]);
    }
    for (int i = 0; i < n; ++i) {
        println(travel[i]);
    }

    return 0;
}
