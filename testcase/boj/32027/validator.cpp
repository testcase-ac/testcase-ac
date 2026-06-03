#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5000, "N");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        inf.readToken("L|R", "D_i");
        inf.readEoln();

        ensuref(!seen[a], "duplicate height at row %d: %d", i, a);
        seen[a] = true;
    }

    inf.readEof();
}
