#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    int k = inf.readInt(1, n * m, "k");
    inf.readEoln();

    vector<vector<bool>> occupied(n + 1, vector<bool>(m + 1, false));
    for (int i = 1; i <= k; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, m, "y_i");
        inf.readEoln();

        ensuref(!occupied[x][y],
                "duplicate student coordinate at index %d: (%d, %d)", i, x, y);
        occupied[x][y] = true;
    }

    inf.readInt(1, k, "s");
    inf.readEoln();
    inf.readEof();
}
