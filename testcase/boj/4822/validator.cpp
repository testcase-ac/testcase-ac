#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxScore = 1000000;

    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 20, "n");
        inf.readSpace();
        int m = inf.readInt(0, 1000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        setTestCase(caseIndex++);
        ensuref(2 <= n, "n must be at least 2 unless this is the terminator");
        ensuref(1 <= m, "m must be at least 1 unless this is the terminator");

        set<string> teams;
        for (int i = 0; i < n; ++i) {
            string team = inf.readLine("[A-Za-z]{1,30}", "team_name");
            // CHECK: Distinct team names are required so match lines identify teams unambiguously.
            ensuref(teams.insert(team).second, "duplicate team name: %s", team.c_str());
        }

        int unplayed = 0;
        for (int i = 0; i < m; ++i) {
            string team1 = inf.readToken("[A-Za-z]{1,30}", "team1");
            ensuref(teams.count(team1), "unknown team1 at match %d: %s", i + 1, team1.c_str());
            inf.readSpace();

            string vs = inf.readToken("[a-z]{2}", "vs");
            ensuref(vs == "vs", "expected vs at match %d", i + 1);
            inf.readSpace();

            string team2Colon = inf.readToken("[A-Za-z]{1,30}:", "team2_colon");
            string team2 = team2Colon.substr(0, team2Colon.size() - 1);
            ensuref(teams.count(team2), "unknown team2 at match %d: %s", i + 1, team2.c_str());
            ensuref(team1 != team2, "same team appears twice at match %d: %s", i + 1, team1.c_str());
            inf.readSpace();

            // CHECK: The statement gives no upper bound for played scores; this cap keeps inputs practical.
            int x = inf.readInt(-1, kMaxScore, "x");
            inf.readSpace();
            int y = inf.readInt(-1, kMaxScore, "y");
            inf.readEoln();

            bool isUnplayed = x == -1 && y == -1;
            bool isPlayed = x >= 0 && y >= 0;
            ensuref(isUnplayed || isPlayed,
                    "scores at match %d must be both non-negative or both -1", i + 1);
            if (isUnplayed) {
                ++unplayed;
            }
        }

        ensuref(unplayed <= 12, "too many unplayed games: %d", unplayed);
    }

    inf.readEof();
}
