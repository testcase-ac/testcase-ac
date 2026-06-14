#include "testlib.h"
#include <vector>
using namespace std;

long long randomCost(bool allowHuge) {
    if (allowHuge && rnd.next(4) == 0) {
        return rnd.next(999999990, 1000000000);
    }
    if (rnd.next(5) == 0) {
        return 0;
    }
    return rnd.next(1, 30);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    vector<vector<long long>> grid(n, vector<long long>(m, -1));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(5) == 0) {
                    grid[i][j] = -2;
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int roll = rnd.next(100);
                if (roll < 18) {
                    grid[i][j] = -2;
                } else if (roll < 43) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = randomCost(false);
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = -2;
            }
        }
        for (int j = 0; j < m; ++j) {
            grid[0][j] = randomCost(false);
        }
        for (int i = 0; i < n; ++i) {
            grid[i][m - 1] = randomCost(false);
        }
        for (int i = 1; i < n; ++i) {
            if (rnd.next(3) != 0) {
                grid[i][rnd.next(m)] = randomCost(false);
            }
        }
        for (int j = 0; j + 1 < m; ++j) {
            if (rnd.next(3) != 0) {
                grid[rnd.next(n)][j] = randomCost(false);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int roll = rnd.next(100);
                if (roll < 12) {
                    grid[i][j] = -2;
                } else if (roll < 28) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = randomCost(true);
                }
            }
        }
    } else {
        int cutRow = rnd.next(1, n - 1);
        int gate = rnd.next(m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == cutRow && j != gate) {
                    grid[i][j] = -2;
                } else if (rnd.next(100) < 30) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = randomCost(false);
                }
            }
        }
        grid[cutRow][gate] = randomCost(rnd.next(2) == 0);
    }

    grid[0][0] = -1;
    grid[n - 1][m - 1] = -1;

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
