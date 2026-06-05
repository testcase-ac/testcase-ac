#include "testlib.h"

#include <vector>

using namespace std;

int randomModulus() {
    int mode = rnd.next(6);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(2, 9);
    }
    if (mode == 2) {
        return rnd.next(10, 101);
    }
    if (mode == 3) {
        return rnd.next(1000, 32000);
    }
    if (mode == 4) {
        return 32000;
    }
    return rnd.any(vector<int>{2, 3, 5, 7, 11, 17, 31, 257});
}

int randomPower() {
    int mode = rnd.next(5);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return 2;
    }
    if (mode == 2) {
        return rnd.next(3, 12);
    }
    if (mode == 3) {
        return rnd.next(13, 200);
    }
    return rnd.next(30000, 32000);
}

vector<vector<int>> makeMatrix(int n, int mod) {
    int pattern = rnd.next(7);
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    if (pattern == 0) {
        return matrix;
    }

    if (pattern == 1) {
        for (int i = 0; i < n; ++i) {
            matrix[i][i] = rnd.next(0, mod - 1);
        }
        return matrix;
    }

    if (pattern == 2) {
        for (int row = 0; row < n; ++row) {
            for (int col = row; col < n; ++col) {
                matrix[row][col] = rnd.next(0, mod - 1);
            }
        }
        return matrix;
    }

    if (pattern == 3) {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (rnd.next(100) < 25) {
                    matrix[row][col] = rnd.next(0, mod - 1);
                }
            }
        }
        return matrix;
    }

    if (pattern == 4) {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                matrix[row][col] = (row + col + rnd.next(0, 2)) % mod;
            }
        }
        return matrix;
    }

    if (pattern == 5) {
        int hi = rnd.next(0, mod - 1);
        int lo = rnd.next(0, hi);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                matrix[row][col] = rnd.next(lo, hi);
            }
        }
        return matrix;
    }

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            matrix[row][col] = rnd.next(0, mod - 1);
        }
    }
    return matrix;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 6);
    for (int tc = 0; tc < cases; ++tc) {
        int n;
        if (tc == 0 && rnd.next(3) == 0) {
            n = 1;
        } else {
            n = rnd.next(1, 8);
        }

        int mod = randomModulus();
        int power = randomPower();
        println(n, mod, power);

        vector<vector<int>> matrix = makeMatrix(n, mod);
        for (int row = 0; row < n; ++row) {
            println(matrix[row]);
        }
    }

    println(0, 0, 0);
    return 0;
}
