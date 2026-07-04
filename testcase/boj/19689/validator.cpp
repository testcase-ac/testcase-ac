#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 500000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 500000, "C");
    inf.readSpace();
    int d = inf.readInt(1, max(r, c), "D");
    inf.readSpace();
    int k = inf.readInt(1, 500000, "K");
    inf.readEoln();

    long long cells = 1LL * r * c;
    ensuref(2 <= cells && cells <= 500000LL, "R*C must be between 2 and 500000, got %lld", cells);
    ensuref(k <= cells, "K must be at most R*C, got K=%d and R*C=%lld", k, cells);

    int mushrooms = 0;
    int sprinklers = 0;
    for (int i = 0; i < r; ++i) {
        string row = inf.readToken("[.MS]{1,500000}", "row");
        inf.readEoln();

        ensuref((int)row.size() == c, "row %d length must be C=%d, got %d", i + 1, c, (int)row.size());
        for (char ch : row) {
            if (ch == 'M') {
                ++mushrooms;
            } else if (ch == 'S') {
                ++sprinklers;
            }
        }
    }

    ensuref(mushrooms >= 1, "there must be at least one mushroom");
    ensuref(sprinklers >= 1, "there must be at least one sprinkler");

    inf.readEof();
}
