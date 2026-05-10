#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of cities, M: number of roads in the set to be chosen
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(N - 1, 1000, "M");
    inf.readEoln();

    // Read adjacency matrix: exactly N lines, each exactly N chars, only 'Y' or 'N'
    vector<string> mat(N);
    for (int i = 0; i < N; ++i) {
        mat[i] = inf.readLine("[YN]{1,50}", "row");  // rough bound
        ensuref((int)mat[i].size() == N,
                "Row %d length must be exactly N (%d), but is %d",
                i, N, (int)mat[i].size());
    }

    // Enforce constraints:
    // 1) No self-loop: diagonal must be 'N'
    for (int i = 0; i < N; ++i) {
        ensuref(mat[i][i] == 'N',
                "Diagonal entry (%d,%d) must be 'N', but is '%c'",
                i, i, mat[i][i]);
    }

    // 2) Symmetry: mat[i][j] == mat[j][i]
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            ensuref(mat[i][j] == mat[j][i],
                    "Matrix must be symmetric: mat[%d][%d]='%c', mat[%d][%d]='%c'",
                    i, j, mat[i][j], j, i, mat[j][i]);
        }
    }

    // Note: The statement does NOT require the whole graph to be connected,
    // nor guarantee existence of a connected subset of size M.
    // Example 3,5 show disconnected graphs and cases where answer = -1,
    // so we must NOT enforce connectivity or existence of such a subset here.

    inf.readEof();
}
