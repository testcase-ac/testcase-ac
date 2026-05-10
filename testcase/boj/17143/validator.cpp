#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions and number of sharks
    int R = inf.readInt(2, 100, "R");
    inf.readSpace();
    int C = inf.readInt(2, 100, "C");
    inf.readSpace();
    int M = inf.readInt(0, R * C, "M");
    inf.readEoln();

    // Track used positions and shark sizes for uniqueness
    vector< vector<bool> > usedPos(R + 1, vector<bool>(C + 1, false));
    vector<bool> usedSize(10000 + 1, false);

    for (int i = 0; i < M; i++) {
        // Shark parameters: r, c, s, d, z
        int r = inf.readInt(1, R, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, C, "c_i");
        inf.readSpace();
        int s = inf.readInt(0, 1000, "s_i");
        inf.readSpace();
        int d = inf.readInt(1, 4, "d_i");
        inf.readSpace();
        int z = inf.readInt(1, 10000, "z_i");
        inf.readEoln();

        // No two sharks start in the same cell
        ensuref(!usedPos[r][c],
                "Duplicate shark position at shark index %d: (%d, %d)", 
                i + 1, r, c);
        usedPos[r][c] = true;

        // Shark sizes are unique
        ensuref(!usedSize[z],
                "Duplicate shark size at shark index %d: size %d", 
                i + 1, z);
        usedSize[z] = true;
    }

    inf.readEof();
    return 0;
}
