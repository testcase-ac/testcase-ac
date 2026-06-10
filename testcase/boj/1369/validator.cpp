#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<vector<int>> reachable(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = inf.readInt(0, 1000000, "a_ij");
            if (value != 0) {
                bool from_start = (i == 0 && j == 0);
                bool from_top = (i > 0 && reachable[i - 1][j]);
                bool from_left = (j > 0 && reachable[i][j - 1]);
                reachable[i][j] = from_start || from_top || from_left;
            }

            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(reachable[n - 1][n - 1],
            "no valid path from (1, 1) to (N, N) through nonzero cells");
    inf.readEof();
}
