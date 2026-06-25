#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int randomDivisor(int k) {
    vector<int> divisors;
    for (int d = 1; d <= k; ++d) {
        if (k % d == 0) {
            divisors.push_back(d);
        }
    }
    return rnd.any(divisors);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 15);
    }

    int k;
    if (mode == 0) {
        k = rnd.next(1, n);
    } else if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = n;
    } else if (mode == 3) {
        k = randomDivisor(rnd.next(1, n));
    } else {
        k = rnd.next(1, n);
    }

    vector<vector<int>> maze(n, vector<int>(n, 0));

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                maze[i][j] = (rnd.next(0, 99) < 65 ? 1 : 0);
            }
        }
    } else if (mode == 3) {
        int clearRow = rnd.next(0, n - 1);
        int clearCol = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                maze[i][j] = 1;
            }
        }
        for (int j = 0; j < n; ++j) {
            maze[clearRow][j] = 0;
        }
        for (int i = 0; i < n; ++i) {
            maze[i][clearCol] = 0;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(0, 99) < 15) {
                    maze[i][j] = 0;
                }
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                maze[i][j] = ((i + j + rnd.next(0, 1)) % 3 == 0 ? 1 : 0);
            }
        }
    } else if (mode == 5) {
        int wallPercent = rnd.next(10, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                maze[i][j] = (rnd.next(0, 99) < wallPercent ? 1 : 0);
            }
        }
    }

    maze[0][0] = 0;

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(maze[i]);
    }

    return 0;
}
