#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string ranks = "23456789TJQKA";
    const string suits = "DCHS";

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        set<string> seen;

        for (int i = 0; i < 26; ++i) {
            string card = inf.readToken("[23456789TJQKA][DCHS]", "card");
            ensuref(ranks.find(card[0]) != string::npos, "invalid rank in card %s", card.c_str());
            ensuref(suits.find(card[1]) != string::npos, "invalid suit in card %s", card.c_str());
            ensuref(seen.insert(card).second, "duplicate card in hand: %s", card.c_str());

            if (i == 25) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
