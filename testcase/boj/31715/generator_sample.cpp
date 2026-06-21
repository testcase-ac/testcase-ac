#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedHeight(int x) {
    return max(1, min(100000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 10);
    int d = rnd.next(1, 30);

    if (mode == 4) {
        n = rnd.next(1, 3);
        m = rnd.next(8, 20);
    } else if (mode == 5) {
        n = rnd.next(6, 12);
        m = rnd.next(1, 4);
        d = rnd.next(1, 100000);
    }

    vector<vector<int>> h(n, vector<int>(m));

    if (mode == 0) {
        int hi = rnd.next(5, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.next(1, hi);
            }
        }
    } else if (mode == 1) {
        d = rnd.next(1, 8);
        int start = rnd.next(1, 20);
        int step = rnd.next(d + 1, d + 12);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = boundedHeight(start + i * step + rnd.next(0, 5));
            }
        }
    } else if (mode == 2) {
        d = rnd.next(1, 5);
        int high = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            int rowBase = high - i * rnd.next(0, 8);
            for (int j = 0; j < m; ++j) {
                h[i][j] = boundedHeight(rowBase - rnd.next(0, 20));
            }
        }
    } else if (mode == 3) {
        d = rnd.next(1, 20);
        vector<int> palette;
        int colors = rnd.next(1, 4);
        for (int i = 0; i < colors; ++i) {
            palette.push_back(rnd.next(1, 60));
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.any(palette);
            }
        }
    } else if (mode == 4) {
        d = rnd.next(1, 50);
        int pivot = rnd.next(1, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j < pivot) {
                    h[i][j] = boundedHeight(20 + i * rnd.next(0, 4) + rnd.next(0, 3));
                } else {
                    h[i][j] = boundedHeight(80 - i * rnd.next(0, 4) - rnd.next(0, 3));
                }
            }
            shuffle(h[i].begin(), h[i].end());
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] = rnd.next(1, 100000);
            }
        }
    }

    println(n, m, d);
    for (int i = 0; i < n; ++i) {
        println(h[i]);
    }

    return 0;
}
