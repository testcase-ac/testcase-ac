#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    ensuref(m % 2 == 0, "m must be even: %d", m);

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[A-Z.]{1,50}", "row");
        inf.readEoln();

        ensuref((int)row.size() == m, "row %d length is %d, expected %d", i + 1,
                (int)row.size(), m);
        for (int j = 0; j < m / 2; ++j) {
            char left = row[j];
            char right = row[m - 1 - j];
            ensuref(left == '.' || right == '.',
                    "row %d mirrored positions %d and %d both contain paint", i + 1,
                    j + 1, m - j);
        }
    }

    inf.readEof();
}
