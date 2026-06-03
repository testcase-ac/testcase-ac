#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 10, "M");
    inf.readSpace();
    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    inf.readInt(0, 5, "U");
    inf.readSpace();
    inf.readInt(0, 5, "L");
    inf.readSpace();
    inf.readInt(0, 5, "R");
    inf.readSpace();
    inf.readInt(0, 5, "D");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        string row = inf.readToken("[a-z]{1,10}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1, (int)row.size(), n);
        inf.readEoln();
    }

    inf.readEof();
}
