#include "testlib.h"

#include <vector>
using namespace std;

int randomBit() {
    return rnd.next(0, 1);
}

vector<vector<int>> makeUnknownMask(int n, int mode) {
    vector<vector<int>> unknown(n, vector<int>(n, 0));

    if (mode == 0) {
        return unknown;
    }

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            unknown[i][rnd.next(0, n - 1)] = 1;
        }
        return unknown;
    }

    if (mode == 2) {
        for (int j = 0; j < n; ++j) {
            unknown[rnd.next(0, n - 1)][j] = 1;
        }
        return unknown;
    }

    if (mode == 3) {
        int rows = rnd.next(1, n);
        int cols = rnd.next(1, n);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                unknown[i][j] = 1;
            }
        }
        return unknown;
    }

    if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                unknown[i][j] = ((i + j) % 2 == 0);
            }
        }
        return unknown;
    }

    if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                unknown[i][j] = 1;
            }
        }
        return unknown;
    }

    int percent = rnd.next(15, 75);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            unknown[i][j] = rnd.next(1, 100) <= percent;
        }
    }
    return unknown;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc == 0 ? rnd.next(0, 6) : rnd.next(0, 6);
        int n = rnd.next(1, 8);
        if (mode == 3) {
            n = rnd.next(2, 8);
        }

        vector<vector<int>> full(n, vector<int>(n));
        vector<int> rowChecksum(n, 0), colChecksum(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                full[i][j] = randomBit();
                rowChecksum[i] ^= full[i][j];
                colChecksum[j] ^= full[i][j];
            }
        }

        vector<vector<int>> unknown = makeUnknownMask(n, mode);

        println(n);
        for (int i = 0; i < n; ++i) {
            vector<int> row(n);
            for (int j = 0; j < n; ++j) {
                row[j] = unknown[i][j] ? -1 : full[i][j];
            }
            println(row);
        }

        for (int i = 0; i < n; ++i) {
            vector<int> row(n);
            for (int j = 0; j < n; ++j) {
                if (unknown[i][j]) {
                    row[j] = rnd.next(1, 1000);
                } else {
                    row[j] = 0;
                }
            }
            println(row);
        }

        println(rowChecksum);
        println(colChecksum);
    }

    return 0;
}
