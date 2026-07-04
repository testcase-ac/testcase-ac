#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    int landCount = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[.#]{1,100}", "row");
        inf.readEoln();

        ensuref(static_cast<int>(row.size()) == m,
                "row %d has length %d, expected %d", i + 1,
                static_cast<int>(row.size()), m);
        for (char cell : row) {
            if (cell == '.') {
                ++landCount;
            }
        }
    }

    ensuref(landCount > 0, "map must contain at least one land cell");
    inf.readEof();
}
