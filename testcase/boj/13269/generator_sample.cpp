#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);

    if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
        m = rnd.next(6, 12);
    }

    vector<vector<int>> top(n, vector<int>(m, 0));
    vector<vector<int>> blocks(n, vector<int>(m, 0));
    int maxHeight = rnd.any(vector<int>{1, 2, 5, 20, 100});

    if (mode == 0) {
        // Empty footprint, with projections chosen independently.
        for (int i = 0; i < n; ++i) {
            fill(top[i].begin(), top[i].end(), 0);
        }
    } else {
        int density = rnd.next(20, 85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < density) {
                    top[i][j] = 1;
                    blocks[i][j] = rnd.next(1, maxHeight);
                }
            }
        }

        if (mode == 3) {
            int emptyRow = rnd.next(0, n - 1);
            for (int j = 0; j < m; ++j) {
                top[emptyRow][j] = 0;
                blocks[emptyRow][j] = 0;
            }
        }
        if (mode == 4) {
            int emptyColumn = rnd.next(0, m - 1);
            for (int i = 0; i < n; ++i) {
                top[i][emptyColumn] = 0;
                blocks[i][emptyColumn] = 0;
            }
        }
        if (mode == 5 && rnd.next(2) == 0) {
            top[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = 1;
        }
    }

    vector<int> front(m, 0), right(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            front[j] = max(front[j], blocks[i][j]);
            right[i] = max(right[i], blocks[i][j]);
        }
    }

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            front[rnd.next(0, m - 1)] = rnd.next(1, 100);
        }
        if (rnd.next(2) == 0) {
            right[rnd.next(0, n - 1)] = rnd.next(1, 100);
        }
    } else if (mode == 5) {
        if (rnd.next(2) == 0) {
            front[rnd.next(0, m - 1)] = 0;
        } else {
            right[rnd.next(0, n - 1)] = 0;
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(top[i]);
    }
    println(front);
    println(right);

    return 0;
}
