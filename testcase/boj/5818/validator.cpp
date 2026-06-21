#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int low = (i == j ? 0 : 1);
            cost[i][j] = inf.readInt(low, 1000000, "meeting_cost");

            if (i == j) {
                ensuref(cost[i][j] == 0,
                        "diagonal entry (%d, %d) must be 0, found %d",
                        i + 1, j + 1, cost[i][j]);
            } else if (j < i) {
                ensuref(cost[i][j] == cost[j][i],
                        "matrix is not symmetric at (%d, %d): %d != %d",
                        i + 1, j + 1, cost[i][j], cost[j][i]);
            }
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "assignment_cost");
    }
    inf.readEoln();

    inf.readEof();
}
