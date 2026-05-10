#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // 2. Read type array
    vector<int> type(N);
    for (int i = 0; i < N; ++i) {
        type[i] = inf.readInt(0, 2, format("type[%d]", i+1));
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read w[i][j] matrix
    vector<vector<int>> w(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            w[i][j] = inf.readInt(0, 1000, format("w[%d][%d]", i+1, j+1));
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // 4. Check symmetry and diagonal
    for (int i = 0; i < N; ++i) {
        ensuref(w[i][i] == 0, "w[%d][%d] must be 0 (diagonal)", i+1, i+1);
        for (int j = 0; j < N; ++j) {
            ensuref(w[i][j] == w[j][i], "w[%d][%d] != w[%d][%d] (matrix must be symmetric)", i+1, j+1, j+1, i+1);
        }
    }

    inf.readEof();
}
