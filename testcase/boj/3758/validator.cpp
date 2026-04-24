#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read header: n, k, t, m
        int n = inf.readInt(3, 100, "n");
        inf.readSpace();
        int k = inf.readInt(3, 100, "k");
        inf.readSpace();
        int t = inf.readInt(1, n, "t");
        inf.readSpace();
        int m = inf.readInt(3, 10000, "m");
        inf.readEoln();

        // Track which teams submitted at least once
        vector<bool> seen(n+1, false);

        // Read the m log entries
        for (int i = 0; i < m; i++) {
            int team_id = inf.readInt(1, n, "team_id");
            inf.readSpace();
            int prob_id = inf.readInt(1, k, "prob_id");
            inf.readSpace();
            int score = inf.readInt(0, 100, "score");
            inf.readEoln();

            seen[team_id] = true;
        }

        // Validate that every team made at least one submission
        for (int team = 1; team <= n; team++) {
            ensuref(seen[team],
                    "In test case %d: team %d has no submissions, "
                    "but every team must submit at least once",
                    tc, team);
        }
    }

    inf.readEof();
    return 0;
}
