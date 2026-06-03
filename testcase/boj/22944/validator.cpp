#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 500, "N");
    inf.readSpace();
    inf.readInt(1, 10000, "H");
    inf.readSpace();
    inf.readInt(1, 5000, "D");
    inf.readEoln();

    int startCount = 0;
    int endCount = 0;
    int umbrellaCount = 0;

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[USE.]{4,500}", "grid_row");
        inf.readEoln();

        ensuref((int)row.size() == n, "row %d length is %d, expected %d", i + 1, (int)row.size(), n);
        for (char cell : row) {
            if (cell == 'S') {
                ++startCount;
            } else if (cell == 'E') {
                ++endCount;
            } else if (cell == 'U') {
                ++umbrellaCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one S, found %d", startCount);
    ensuref(endCount == 1, "expected exactly one E, found %d", endCount);
    ensuref(umbrellaCount <= 10, "expected at most 10 umbrellas, found %d", umbrellaCount);

    inf.readEof();
}
