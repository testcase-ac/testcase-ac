#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(3, 50, "W");
    inf.readSpace();
    int h = inf.readInt(3, 50, "H");
    inf.readEoln();

    int playerCount = 0;
    for (int y = 0; y < h; ++y) {
        string row = inf.readToken("[PGT#\\.]{3,50}", "row");
        inf.readEoln();

        ensuref((int)row.size() == w, "row %d has length %d, expected %d",
                y + 1, (int)row.size(), w);

        for (int x = 0; x < w; ++x) {
            char cell = row[x];
            if (cell == 'P') {
                ++playerCount;
            }
            if (y == 0 || y == h - 1 || x == 0 || x == w - 1) {
                ensuref(cell == '#', "border cell (%d, %d) is '%c', expected '#'",
                        y + 1, x + 1, cell);
            }
        }
    }

    ensuref(playerCount == 1, "expected exactly one P, found %d", playerCount);
    inf.readEof();
}
