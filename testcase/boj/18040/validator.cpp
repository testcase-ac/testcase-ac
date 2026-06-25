#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[GB]{1,1000}", "row");
        ensuref(static_cast<int>(row.size()) == m,
                "row %d has length %d, expected %d", i + 1,
                static_cast<int>(row.size()), m);
        inf.readEoln();
    }

    inf.readEof();
}
