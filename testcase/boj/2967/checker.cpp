#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int R, C;
vector<string> grid;

// This function reads two squares from 'stream', checks validity:
//  - each square is within bounds,
//  - all cells of each square are 'x',
//  - the union of the two squares exactly matches the 'x' cells in the grid.
// If any check fails, it calls quitf(_wa, ...) when stream==ouf or quitf(_fail, ...) when stream==ans.
void readAns(InStream &stream) {
    struct Sq { int r, c, s; };
    vector<Sq> sqs(2);
    for (int i = 0; i < 2; i++) {
        sqs[i].r = stream.readInt(1, R,   format("r_of_sq_%d", i+1).c_str());
        sqs[i].c = stream.readInt(1, C,   format("c_of_sq_%d", i+1).c_str());
        int maxS = min(R, C);
        sqs[i].s = stream.readInt(1, maxS, format("s_of_sq_%d", i+1).c_str());
        // Check bounds
        if (sqs[i].r + sqs[i].s - 1 > R || sqs[i].c + sqs[i].s - 1 > C) {
            stream.quitf(_wa, "square %d is out of bounds: r=%d, c=%d, s=%d", 
                        i+1, sqs[i].r, sqs[i].c, sqs[i].s);
        }
    }
    // Check that every cell in each square is 'x'
    for (int i = 0; i < 2; i++) {
        int r0 = sqs[i].r - 1;
        int c0 = sqs[i].c - 1;
        for (int dr = 0; dr < sqs[i].s; dr++) {
            for (int dc = 0; dc < sqs[i].s; dc++) {
                int rr = r0 + dr, cc = c0 + dc;
                if (grid[rr][cc] != 'x') {
                    stream.quitf(_wa, "square %d covers a '.' at (%d,%d)", 
                                i+1, rr+1, cc+1);
                }
            }
        }
    }
    // Build union of the two squares
    vector< vector<bool> > cover(R, vector<bool>(C, false));
    for (int i = 0; i < 2; i++) {
        int r0 = sqs[i].r - 1;
        int c0 = sqs[i].c - 1;
        for (int dr = 0; dr < sqs[i].s; dr++)
            for (int dc = 0; dc < sqs[i].s; dc++)
                cover[r0+dr][c0+dc] = true;
    }
    // Check that every 'x' in grid is covered, and no extra '.' is covered
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'x' && !cover[i][j]) {
                stream.quitf(_wa, "cell (%d,%d) is 'x' but not covered by any square", i+1, j+1);
            }
            if (grid[i][j] == '.' && cover[i][j]) {
                stream.quitf(_wa, "square covers a '.' at (%d,%d)", i+1, j+1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    R = inf.readInt();
    C = inf.readInt();
    grid.resize(R);
    for (int i = 0; i < R; i++) {
        grid[i] = inf.readToken();
    }
    // Read and validate jury answer
    readAns(ans);
    // Read and validate contestant answer
    readAns(ouf);
    quitf(_ok, "valid decomposition into two squares");
    return 0;
}
