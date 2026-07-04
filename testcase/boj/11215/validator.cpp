#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        string row = inf.readToken("[.X]{1,100}", "row");
        ensuref(static_cast<int>(row.size()) == n,
                "row %d has length %d, expected %d",
                i + 1,
                static_cast<int>(row.size()),
                n);
        inf.readEoln();
    }

    inf.readEof();
}
