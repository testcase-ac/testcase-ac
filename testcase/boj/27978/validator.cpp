#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(3, 500, "H");
    inf.readSpace();
    int w = inf.readInt(3, 500, "W");
    inf.readEoln();

    int shipCount = 0;
    int treasureCount = 0;

    for (int r = 0; r < h; ++r) {
        string row = inf.readLine("[.#*K]{3,500}", "map_row");
        ensuref(static_cast<int>(row.size()) == w,
                "row %d has length %d, expected %d", r + 1, static_cast<int>(row.size()), w);

        for (char cell : row) {
            if (cell == 'K') {
                ++shipCount;
            } else if (cell == '*') {
                ++treasureCount;
            }
        }
    }

    ensuref(shipCount == 1, "map must contain exactly one ship K, found %d", shipCount);
    ensuref(treasureCount == 1, "map must contain exactly one treasure *, found %d", treasureCount);

    inf.readEof();
}
