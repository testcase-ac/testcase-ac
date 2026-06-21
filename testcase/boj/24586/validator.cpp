#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

bool hasValidBobCards(int p, int q, const string& positions) {
    for (int x = 1; x <= 9; ++x) {
        if (x == p || x == q) {
            continue;
        }
        for (int y = x + 1; y <= 9; ++y) {
            if (y == p || y == q) {
                continue;
            }

            int aliceIndex = 0;
            int bobIndex = 0;
            int aliceCards[2] = {p, q};
            int bobCards[2] = {x, y};
            int table[4];

            for (int i = 0; i < 4; ++i) {
                if (positions[i] == 'A') {
                    table[i] = aliceCards[aliceIndex++];
                } else {
                    table[i] = bobCards[bobIndex++];
                }
            }

            if (is_sorted(table, table + 4) &&
                adjacent_find(table, table + 4) == table + 4) {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 9, "p");
    inf.readSpace();
    int q = inf.readInt(1, 9, "q");
    inf.readEoln();
    ensuref(p < q, "Alice's cards must satisfy p < q, got %d %d", p, q);

    string positions = inf.readToken("[AB]{4}", "positions");
    inf.readEoln();
    ensuref(count(positions.begin(), positions.end(), 'A') == 2,
            "positions must contain exactly two A characters, got %s",
            positions.c_str());
    ensuref(count(positions.begin(), positions.end(), 'B') == 2,
            "positions must contain exactly two B characters, got %s",
            positions.c_str());
    ensuref(hasValidBobCards(p, q, positions),
            "positions are not achievable by correctly sorted distinct cards: p=%d q=%d positions=%s",
            p, q, positions.c_str());

    inf.readEof();
}
