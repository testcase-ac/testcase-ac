#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int center, int spread) {
    return max(-1000, min(1000, center + rnd.next(-spread, spread)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        k = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        k = rnd.next(2, n);
    } else if (mode == 3) {
        n = rnd.next(5, 10);
        k = rnd.next(2, n);
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        k = rnd.next(1, n);
    } else {
        n = rnd.next(7, 10);
        k = rnd.next(2, n);
    }

    vector<vector<int>> c(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                c[i][j] = c[j][i] = rnd.next(-3, 3);
            }
        }
    } else if (mode == 1) {
        int lo = rnd.next(-1000, -200);
        int hi = rnd.next(-199, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                c[i][j] = c[j][i] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 2) {
        int lo = rnd.next(0, 200);
        int hi = rnd.next(201, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                c[i][j] = c[j][i] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool sameGroup = (i < split) == (j < split);
                int center = sameGroup ? rnd.next(250, 900) : rnd.next(-900, -250);
                c[i][j] = c[j][i] = boundedValue(center, 120);
            }
        }
    } else if (mode == 4) {
        int zeroChance = rnd.next(15, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(100) < zeroChance) {
                    c[i][j] = c[j][i] = 0;
                } else {
                    c[i][j] = c[j][i] = rnd.next(-1000, 1000);
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                c[i][j] = c[j][i] = rnd.next(-50, 50);
            }
        }

        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pairs.push_back({i, j});
            }
        }
        shuffle(pairs.begin(), pairs.end());
        int boosted = rnd.next(1, min<int>(pairs.size(), n));
        for (int idx = 0; idx < boosted; ++idx) {
            int i = pairs[idx].first;
            int j = pairs[idx].second;
            c[i][j] = c[j][i] = rnd.next(700, 1000);
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(c[i]);
    }

    return 0;
}
