#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        string row = inf.readLine("[EW]{1,10000}", "d_i");
        ensuref(static_cast<int>(row.size()) == n,
                "data row %d has length %d, expected %d", i,
                static_cast<int>(row.size()), n);
    }

    inf.readEof();
}
