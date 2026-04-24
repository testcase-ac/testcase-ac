#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of tanks and grid size
    int N = inf.readInt(5, 500, "N");
    inf.readEoln();

    // Track occupied cells to ensure no duplicates
    vector<vector<bool>> seen(N+1, vector<bool>(N+1, false));

    for (int i = 0; i < N; i++) {
        // Read tank position (row, column)
        int r = inf.readInt(1, N, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, N, "c_i");
        inf.readEoln();

        // Ensure no two tanks share the same cell
        ensuref(!seen[r][c],
                "Duplicate tank position at input line %d: (%d, %d)",
                i + 2, r, c);
        seen[r][c] = true;
    }

    inf.readEof();
    return 0;
}
