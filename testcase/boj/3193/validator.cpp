#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: board size, K: number of rotations
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 500000, "K");
    inf.readEoln();

    vector<string> board(N);
    int ballCount = 0;

    for (int i = 0; i < N; ++i) {
        board[i] = inf.readToken("[.XL]{"+toString(N)+","+toString(N)+"}", "board_row");
        ensuref((int)board[i].size() == N,
                "Row %d must have exactly N=%d characters, got %d",
                i + 1, N, (int)board[i].size());
        for (int j = 0; j < N; ++j) {
            char c = board[i][j];
            if (c == 'L') ballCount++;
            // '.' or 'X' are already guaranteed by regex
        }
        inf.readEoln();
    }

    // Exactly one ball must exist
    ensuref(ballCount == 1,
            "There must be exactly one ball 'L', but found %d", ballCount);

    // Read K rotation commands, each line is exactly 'L' or 'D'
    for (int i = 0; i < K; ++i) {
        string cmd = inf.readToken("[LD]", "rotation_command");
        ensuref(cmd.size() == 1, "Rotation command line %d must be a single character", i + 1);
        inf.readEoln();
    }

    inf.readEof();
}
