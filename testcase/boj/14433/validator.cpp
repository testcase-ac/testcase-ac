#include "testlib.h"

void readPreferences(int count, int n, int m, const char* playerName, const char* pickName) {
    for (int idx = 1; idx <= count; ++idx) {
        inf.readInt(1, n, playerName);
        inf.readSpace();
        inf.readInt(1, m, pickName);
        inf.readEoln();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300, "M");
    inf.readSpace();
    int k1 = inf.readInt(1, 500, "K1");
    inf.readSpace();
    int k2 = inf.readInt(1, 500, "K2");
    inf.readEoln();

    // CHECK: the statement does not require distinct (player, trollpick) pairs.
    readPreferences(k1, n, m, "team1_player", "team1_pick");
    readPreferences(k2, n, m, "team2_player", "team2_pick");

    inf.readEof();
}
