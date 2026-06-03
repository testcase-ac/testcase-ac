#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "m");
    inf.readEoln();

    int cat_count = 0;
    int exit_count = 0;

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[CDEFLX]{2,1000}", "row");
        inf.readEoln();

        ensuref((int)row.size() == m, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), m);

        for (int j = 0; j < m; ++j) {
            if (row[j] == 'C') {
                ++cat_count;
            } else if (row[j] == 'E') {
                ++exit_count;
            }

            ensuref(i + 1 != n || row[j] != 'X',
                    "bottom row contains X at column %d", j + 1);
        }
    }

    ensuref(cat_count == 1, "expected exactly one C, found %d", cat_count);
    ensuref(exit_count == 1, "expected exactly one E, found %d", exit_count);

    inf.readEof();
}
