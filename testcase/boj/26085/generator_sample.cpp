#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 12);
    int m = rnd.next(3, 12);
    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 0) {
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (first + i + j) % 2;
            }
        }
    } else if (mode == 1) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = value;
            }
        }
    } else if (mode == 2) {
        vector<int> values(n * m);
        if ((n * m) % 2 == 0) {
            int ones = rnd.next(0, n * m / 2) * 2;
            for (int i = 0; i < ones; ++i) {
                values[i] = 1;
            }
        } else {
            int oddValue = rnd.next(0, 1);
            int oddCount = rnd.next(0, (n * m - 1) / 2) * 2 + 1;
            for (int i = 0; i < oddCount; ++i) {
                values[i] = oddValue;
            }
            for (int i = oddCount; i < n * m; ++i) {
                values[i] = 1 - oddValue;
            }
        }
        shuffle(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = values[i * m + j];
            }
        }
    } else if (mode == 3) {
        int vertical = rnd.next(0, 1);
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = vertical ? (first + j) % 2 : (first + i) % 2;
            }
        }
    } else if (mode == 4) {
        int h = rnd.next(1, 3);
        int w = rnd.next(1, 3);
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (first + i / h + j / w) % 2;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int bias = rnd.next(0, 4);
                grid[i][j] = rnd.next(0, 9) < bias ? 1 : 0;
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
