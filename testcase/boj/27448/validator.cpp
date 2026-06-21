#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 80, "N");
    inf.readSpace();
    int m = inf.readInt(1, 80, "M");
    inf.readSpace();
    inf.readInt(1, 80, "F");
    inf.readEoln();

    bool hasWood = false;
    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[#.]{1,80}", "row");
        ensuref((int)row.size() == m, "row %d length is %d, expected %d",
                i + 1, (int)row.size(), m);
        for (char cell : row) {
            hasWood = hasWood || cell == '#';
        }
    }

    ensuref(hasWood, "grid must contain at least one #");
    inf.readEof();
}
