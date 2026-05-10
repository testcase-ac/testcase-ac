#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of participants
    int N = inf.readInt(1, 16, "N");
    inf.readEoln();

    // Guilt indices: N integers, 300..800
    vector<int> guilt = inf.readInts(N, 300, 800, "g_i");
    inf.readEoln();

    // R: N lines, each with N integers, each in [-26, -1] U [1, 26]
    vector<vector<int>> R(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val = inf.readInt(-26, 26, "R_ij");
            ensuref(val <= -1 || val >= 1,
                    "R[%d][%d] must be in [-26,-1] or [1,26], got %d", i, j, val);
            R[i][j] = val;
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Eun-jin's participant index
    int me = inf.readInt(0, N - 1, "me");
    inf.readEoln();

    // No further global structural guarantees to check from statement:
    // - No guarantee about uniqueness of anything, connectivity, etc.
    // - The game process and "optimal play" are for solutions, not validator.
    // Thus we only enforce the numeric and format constraints above.

    inf.readEof();
}
