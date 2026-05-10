#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // For each board, store R, C, and the board itself
    vector<int> Rs(N), Cs(N);

    for (int i = 0; i < N; ++i) {
        // Read R_i, C_i
        int R = inf.readInt(1, 40, "R_i");
        inf.readSpace();
        int C = inf.readInt(1, 40, "C_i");
        inf.readEoln();

        ensuref(1LL * R * C <= 40, "R_i * C_i must be <= 40, but got %d * %d = %lld at board %d", R, C, 1LL * R * C, i+1);

        Rs[i] = R;
        Cs[i] = C;

        int cntA = 0, cntB = 0;
        for (int r = 0; r < R; ++r) {
            std::string row = inf.readLine("[ABC]{"+to_string(C)+"}", "board_row");
            ensuref((int)row.size() == C, "Row %d of board %d does not have C_i=%d characters", r+1, i+1, C);
            for (char ch : row) {
                ensuref(ch == 'A' || ch == 'B' || ch == 'C', "Invalid character '%c' at board %d row %d", ch, i+1, r+1);
                if (ch == 'A') cntA++;
                if (ch == 'B') cntB++;
            }
        }
        // Each board: at least one of A or B appears exactly once
        ensuref(cntA >= 1 || cntB >= 1, "At board %d, at least one of A or B must appear", i+1);
        // At least one of A or B appears exactly once
        ensuref(cntA == 1 || cntB == 1, "At board %d, at least one of A or B must appear exactly once (got A=%d, B=%d)", i+1, cntA, cntB);
        // No further restriction: both can be >1 as long as at least one is exactly one
    }

    // 2. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int t = 0; t < T; ++t) {
        int K = inf.readInt(1, N, "K");
        inf.readSpace();
        int U = inf.readInt(1, N, "U");
        inf.readSpace();
        int V = inf.readInt(U, N, "V");
        inf.readEoln();
    }

    inf.readEof();
}
