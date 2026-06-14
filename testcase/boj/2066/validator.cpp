#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<string> seen;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 4; ++col) {
            string card = inf.readToken("[6789TJQKA][SCDH]", "card");
            ensuref(seen.insert(card).second, "duplicate card at row %d column %d: %s",
                    row + 1, col + 1, card.c_str());

            if (col == 3) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(seen.size() == 36, "input must contain all 36 cards");
    inf.readEof();
}
