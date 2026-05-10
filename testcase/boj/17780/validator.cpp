#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, K
    int N = inf.readInt(4, 12, "N");
    inf.readSpace();
    int K = inf.readInt(4, 10, "K");
    inf.readEoln();

    // 2. Read board
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = inf.readInt(0, 2, "board[i][j]");
            if (j != N-1) inf.readSpace();
        }
        inf.readEoln();
    }

    // 3. Read K pieces, check unique positions
    set<pair<int,int>> used;
    for (int i = 0; i < K; ++i) {
        int r = inf.readInt(1, N, "r");
        inf.readSpace();
        int c = inf.readInt(1, N, "c");
        inf.readSpace();
        int d = inf.readInt(1, 4, "d");
        inf.readEoln();

        ensuref(used.count({r, c}) == 0, "Duplicate piece position at piece %d: (%d, %d)", i+1, r, c);
        used.insert({r, c});
    }

    inf.readEof();
}
