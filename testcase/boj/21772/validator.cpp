#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 100, "R");
    inf.readSpace();
    int c = inf.readInt(2, 100, "C");
    inf.readSpace();
    inf.readInt(1, 10, "T");
    inf.readEoln();

    int gCount = 0;
    int sCount = 0;
    int wallCount = 0;

    for (int i = 0; i < r; ++i) {
        string row = inf.readLine("[GS.#]{2,100}", "row");
        ensuref((int)row.size() == c, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), c);

        for (char cell : row) {
            if (cell == 'G') {
                ++gCount;
            } else if (cell == 'S') {
                ++sCount;
            } else if (cell == '#') {
                ++wallCount;
            }
        }
    }

    ensuref(gCount == 1, "expected exactly one G, found %d", gCount);
    ensuref(sCount >= 1, "expected at least one S, found %d", sCount);
    ensuref(wallCount >= 1, "expected at least one #, found %d", wallCount);

    inf.readEof();
}
