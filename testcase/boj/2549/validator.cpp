#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 4;
    const int MN = N * N;

    vector<bool> seen(MN + 1, false);

    for (int r = 0; r < N; ++r) {
        // read 4 integers in [1,16]
        int row[4];
        for (int c = 0; c < N; ++c) {
            row[c] = inf.readInt(1, MN, "tile");
            if (c + 1 < N) inf.readSpace();
        }
        inf.readEoln();

        for (int c = 0; c < N; ++c) {
            int x = row[c];
            ensuref(!seen[x],
                    "Tile number %d appears more than once (at row %d, col %d)",
                    x, r + 1, c + 1);
            seen[x] = true;
        }
    }

    // ensure all tile numbers 1..16 appear exactly once
    for (int x = 1; x <= MN; ++x) {
        ensuref(seen[x], "Tile number %d is missing from the grid", x);
    }

    inf.readEof();
}
