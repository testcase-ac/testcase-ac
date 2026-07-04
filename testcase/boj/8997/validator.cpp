#include "testlib.h"

#include <vector>

using namespace std;

void readSpaces() {
    inf.readSpace();
    while (inf.curChar() == ' ') {
        inf.readSpace();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: T has no statement bound. This cap keeps validated inputs below
    // the local practical scalar-token limit for maximum-size cases.
    int T = inf.readInt(1, 7000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 25, "n");
        inf.readEoln();

        vector<int> wins(n), defeats(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                readSpaces();
            }
            wins[i] = inf.readInt(0, 100, "w_i");
            readSpaces();
            defeats[i] = inf.readInt(0, 100, "d_i");
        }
        inf.readEoln();

        vector<vector<int>> remaining(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i > 0 || j > 0) {
                    readSpaces();
                }
                remaining[i][j] = inf.readInt(0, 10, "a_i_j");
            }
        }
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            ensuref(remaining[i][i] == 0,
                    "case %d has nonzero a[%d][%d]: %d",
                    tc, i + 1, i + 1, remaining[i][i]);
            for (int j = i + 1; j < n; ++j) {
                ensuref(remaining[i][j] == remaining[j][i],
                        "case %d has asymmetric remaining games: a[%d][%d]=%d, a[%d][%d]=%d",
                        tc, i + 1, j + 1, remaining[i][j],
                        j + 1, i + 1, remaining[j][i]);
            }
        }

        int gamesPerTeam = wins[0] + defeats[0];
        for (int j = 0; j < n; ++j) {
            gamesPerTeam += remaining[0][j];
        }

        for (int i = 1; i < n; ++i) {
            int totalGames = wins[i] + defeats[i];
            for (int j = 0; j < n; ++j) {
                totalGames += remaining[i][j];
            }
            ensuref(totalGames == gamesPerTeam,
                    "case %d team %d total games is %d, expected %d",
                    tc, i + 1, totalGames, gamesPerTeam);
        }
    }

    inf.readEof();
}
