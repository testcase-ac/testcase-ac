#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int start = rnd.next(1, n);
    vector<vector<int>> c(n, vector<int>(n, 0));

    if (mode == 0) {
        double p = rnd.next(0.0, 0.35);
        for (int r = 0; r < n; ++r) {
            for (int col = 0; col < n; ++col) {
                if (rnd.next() < p) {
                    c[r][col] = 1;
                }
            }
        }
    } else if (mode == 1) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i + 1 < n; ++i) {
            c[order[i]][order[i + 1]] = 1;
            if (rnd.next(0, 2) == 0) {
                c[order[i + 1]][order[i]] = 1;
            }
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            c[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = 1;
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n);
        for (int r = 0; r < n; ++r) {
            int hi = (r < split ? split : n);
            int lo = (r < split ? 0 : split);
            for (int col = lo; col < hi; ++col) {
                if (rnd.next(0, 3) == 0) {
                    c[r][col] = 1;
                }
            }
        }
        start = rnd.next(1, split);
    } else if (mode == 3) {
        double p = rnd.next(0.55, 0.9);
        for (int r = 0; r < n; ++r) {
            for (int col = 0; col < n; ++col) {
                if (rnd.next() < p) {
                    c[r][col] = 1;
                }
            }
        }
    } else {
        for (int r = 0; r < n; ++r) {
            c[r][r] = 1;
        }
        int edges = rnd.next(0, n * 2);
        for (int i = 0; i < edges; ++i) {
            c[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = 1;
        }
    }

    println(n, start);
    for (int r = 0; r < n; ++r) {
        println(c[r]);
    }

    return 0;
}
