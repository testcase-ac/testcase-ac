#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    vector<vector<int>> a(N, vector<int>(N));
    long long nonZeroCount = 0;

    for (int i = 0; i < N; ++i) {
        vector<int> row = inf.readInts(N, 0, 1024, "board_row");
        inf.readEoln();
        for (int j = 0; j < N; ++j) {
            int v = row[j];
            if (v != 0) {
                nonZeroCount++;
                // must be a power of two, between 2 and 1024 inclusive
                ensuref(v >= 2 && v <= 1024,
                        "Non-zero cell value must be between 2 and 1024, got %d at (%d,%d)",
                        v, i + 1, j + 1);
                // check power of two
                ensuref((v & (v - 1)) == 0,
                        "Non-zero cell value must be a power of 2, got %d at (%d,%d)",
                        v, i + 1, j + 1);
            }
            a[i][j] = v;
        }
    }

    ensuref(nonZeroCount > 0, "At least one block (non-zero cell) must be present on the board");

    inf.readEof();
}
