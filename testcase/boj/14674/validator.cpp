#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int row = 1; row <= n; ++row) {
        int id = inf.readInt(1, n, "i");
        inf.readSpace();
        inf.readInt(1, 100000000, "c");
        inf.readSpace();
        inf.readInt(1, 100000000, "h");
        inf.readEoln();

        ensuref(!seen[id], "duplicate game id %d at row %d", id, row);
        seen[id] = true;
    }

    inf.readEof();
}
