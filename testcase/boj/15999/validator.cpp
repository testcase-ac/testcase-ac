#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[BW]{1,2000}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), m);
        inf.readEoln();
    }

    inf.readEof();
}
