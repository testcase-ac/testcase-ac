#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "m");
    inf.readEoln();

    int epicenters = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[^]{2,1000}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), m);
        for (char cell : row) {
            ensuref(cell == '@' || cell == '.' || cell == '*' || cell == '#' || cell == '|',
                    "invalid character '%c' in row %d", cell, i + 1);
            if (cell == '@') {
                ++epicenters;
            }
        }
    }

    ensuref(epicenters == 1, "expected exactly one epicenter, found %d", epicenters);
    inf.readEof();
}
