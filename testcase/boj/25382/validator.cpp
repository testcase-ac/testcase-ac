#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "n");
    inf.readEoln();

    vector<bool> seenX(n + 1), seenY(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        inf.readInt(a, n, "b_i");
        inf.readEoln();

        ensuref(!seenX[x], "x_i must be distinct: x_%d = %d", i, x);
        ensuref(!seenY[y], "y_i must be distinct: y_%d = %d", i, y);
        seenX[x] = true;
        seenY[y] = true;
    }

    inf.readEof();
}
