#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    int unplayed = 0;
    for (int i = 1; i <= m; ++i) {
        int team1 = inf.readInt(1, n, "team1");
        inf.readSpace();
        int team2 = inf.readInt(1, n, "team2");
        inf.readSpace();
        int result = inf.readInt(0, 2, "result");
        inf.readEoln();

        ensuref(team1 != team2, "game %d has identical teams: %d", i, team1);
        if (result == 0) {
            ++unplayed;
        }
    }

    ensuref(unplayed <= 20, "too many unplayed games: %d", unplayed);
    inf.readEof();
}
