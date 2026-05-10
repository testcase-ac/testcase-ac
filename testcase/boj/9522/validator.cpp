#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of points
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Constraints for coordinates
    const int MINC = 1;
    const int MAXC = 500;

    // We store points to check for duplicates
    // Using bool grid since coordinate bounds are small.
    static bool used[501][501];
    for (int i = 0; i < 501; ++i)
        for (int j = 0; j < 501; ++j)
            used[i][j] = false;

    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(MINC, MAXC, "x");
        inf.readSpace();
        int y = inf.readInt(MINC, MAXC, "y");
        inf.readEoln();

        // Ensure no duplicate points (implied: "N points" as a set)
        ensuref(!used[x][y],
                "Duplicate point detected at index %d: (%d, %d)", i + 1, x, y);
        used[x][y] = true;
    }

    inf.readEof();
}
