#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 4500, "m");
    inf.readEoln();

    vector<vector<bool>> beats(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "round %d has the same cow twice: %d", i + 1, a);
        beats[a][b] = true;
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                beats[i][j] = beats[i][j] || (beats[i][k] && beats[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        ensuref(!beats[i][i], "results are contradictory: cow %d is in a cycle", i);
    }

    inf.readEof();
}
