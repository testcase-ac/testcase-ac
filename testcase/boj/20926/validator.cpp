#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(2, 500, "W");
    inf.readSpace();
    int h = inf.readInt(2, 500, "H");
    inf.readEoln();

    int terraCount = 0;
    int exitCount = 0;
    for (int y = 0; y < h; ++y) {
        string row = inf.readLine("[TRHE0-9]{2,500}", "row");
        ensuref((int)row.size() == w, "row %d has length %d, expected %d", y + 1,
                (int)row.size(), w);

        for (char cell : row) {
            if (cell == 'T') {
                ++terraCount;
            } else if (cell == 'E') {
                ++exitCount;
            }
        }
    }

    ensuref(terraCount == 1, "expected exactly one T, found %d", terraCount);
    ensuref(exitCount == 1, "expected exactly one E, found %d", exitCount);

    inf.readEof();
}
