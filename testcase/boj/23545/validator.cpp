#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    inf.readInt(1, 1000000, "k");
    inf.readEoln();

    const string rowPattern = "[.#]{%d,%d}";
    for (int i = 1; i <= n; ++i) {
        string row = inf.readToken(format(rowPattern.c_str(), m, m), "row");
        inf.readEoln();
        ensuref((int)row.size() == m, "row %d has length %d, expected %d",
                i, (int)row.size(), m);
    }

    inf.readEof();
}
