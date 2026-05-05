#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 9, "N");
    inf.readSpace();
    int K = inf.readInt(1, 6, "K");
    inf.readEoln();

    // 2. Read NxN matrix A
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = inf.readInt(0, 2, format("A_%d_%d", i+1, j+1).c_str());
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // 3. Validate matrix A
    for (int i = 0; i < N; ++i) {
        // Diagonal must be 1
        ensuref(A[i][i] == 1, "A[%d][%d] must be 1 (diagonal)", i+1, i+1);
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            // Off-diagonal must not be 1
            ensuref(A[i][j] != 1, "A[%d][%d] must not be 1 for i != j", i+1, j+1);
            // If A[i][j] == 2 then A[j][i] == 0, and vice versa
            if (A[i][j] == 2) {
                ensuref(A[j][i] == 0, "A[%d][%d]=2 but A[%d][%d]!=0", i+1, j+1, j+1, i+1);
            }
            if (A[i][j] == 0) {
                ensuref(A[j][i] == 2, "A[%d][%d]=0 but A[%d][%d]!=2", i+1, j+1, j+1, i+1);
            }
        }
    }

    // 4. Read Kyunghee's moves (20 integers in [1,N])
    vector<int> kyunghee = inf.readInts(20, 1, N, "kyunghee_moves");
    inf.readEoln();

    // 5. Read Minho's moves (20 integers in [1,N])
    vector<int> minho = inf.readInts(20, 1, N, "minho_moves");
    inf.readEoln();

    // 6. Final EOF
    inf.readEof();
}
