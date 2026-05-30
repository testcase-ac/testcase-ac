#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int readGames(const string& score, int match, int set, const char* side) {
    ensuref(!score.empty(), "match %d set %d has an empty %s score", match, set, side);
    ensuref(score.size() <= 2, "match %d set %d %s score is longer than 2 digits", match, set, side);
    ensuref(score.size() == 1 || score[0] != '0',
            "match %d set %d %s score has a leading zero", match, set, side);
    int value = 0;
    for (char ch : score) {
        ensuref('0' <= ch && ch <= '9', "match %d set %d %s score contains a non-digit", match, set, side);
        value = value * 10 + (ch - '0');
    }
    ensuref(value <= 99, "match %d set %d %s score is greater than 99", match, set, side);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string first = inf.readToken("[a-z]{1,20}", "first_player");
    inf.readSpace();
    string second = inf.readToken("[a-z]{1,20}", "second_player");
    ensuref(first != second, "player names must be different");
    inf.readEoln();

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    for (int match = 1; match <= n; ++match) {
        int sets = 0;
        while (true) {
            ++sets;
            string score = inf.readToken("[0-9]{1,2}:[0-9]{1,2}", format("match_%d_set_%d_score", match, sets));
            size_t colon = score.find(':');
            readGames(score.substr(0, colon), match, sets, "first");
            readGames(score.substr(colon + 1), match, sets, "second");

            char next = inf.readChar();
            if (next == '\n') {
                break;
            }
            ensuref(next == ' ', "match %d set %d must be followed by space or end of line", match, sets);
            ensuref(sets < 5, "match %d contains more than 5 sets", match);
        }

        ensuref(1 <= sets && sets <= 5, "match %d contains %d sets", match, sets);
    }

    inf.readEof();
    return 0;
}
