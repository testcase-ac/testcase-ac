#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    string rowPattern = "[LR]{" + to_string(n) + "}";
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken(rowPattern, "row");
        inf.readEoln();
        ensuref(static_cast<int>(row.size()) == n,
                "row %d has length %d instead of %d", i + 1,
                static_cast<int>(row.size()), n);
    }

    inf.readEof();
}
