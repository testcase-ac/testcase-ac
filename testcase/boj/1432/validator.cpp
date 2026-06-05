#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[01]{1,50}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), n);
        // CHECK: the statement does not forbid self-loops; they just make renumbering impossible.
    }

    inf.readEof();
}
