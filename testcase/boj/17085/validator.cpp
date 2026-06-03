#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 15, "n");
    inf.readSpace();
    int m = inf.readInt(2, 15, "m");
    inf.readEoln();

    int filled = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[.#]{2,15}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), m);
        for (char cell : row) {
            if (cell == '#') {
                ++filled;
            }
        }
        inf.readEoln();
    }

    ensuref(filled >= 2, "at least two '#' cells are needed to place two size-0 crosses");

    inf.readEof();
}
