#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 200000, "N");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        inf.readInt(0, 100, "A");
        inf.readSpace();
        inf.readInt(0, 100, "B");
        inf.readSpace();
        inf.readInt(0, 100, "C");
        inf.readSpace();
        inf.readInt(0, 100, "D");
        inf.readEoln();

        ensuref(!seen[x], "duplicate student number at row %d: %d", i, x);
        seen[x] = true;
    }

    inf.readEof();
}
