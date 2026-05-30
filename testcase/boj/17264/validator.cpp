#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    inf.readInt(0, 100, "W");
    inf.readSpace();
    inf.readInt(0, 100, "L");
    inf.readSpace();
    inf.readInt(1, 100000, "G");
    inf.readEoln();

    for (int i = 0; i < P; ++i) {
        inf.readToken("[A-Z]{1,20}", "player_name");
        inf.readSpace();
        inf.readToken("W|L", "result");
        inf.readEoln();
    }

    for (int i = 0; i < N; ++i) {
        inf.readToken("[A-Z]{1,20}", "game_player_name");
        inf.readEoln();
    }

    inf.readEof();
}
