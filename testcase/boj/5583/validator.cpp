#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 150, "n");
    inf.readSpace();
    int m = inf.readInt(0, (n + 1) / 2, "m");
    inf.readEoln();

    vector<vector<vector<bool>>> reachable(n + 2, vector<vector<bool>>(m + 1));
    reachable[0][0].push_back(true);

    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(0, 10, "k_i");
        reachable[i].assign(m + 1, vector<bool>(k, false));

        set<int> usedColumns;
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int x = inf.readInt(1, 1000, "x_i_j");
            inf.readSpace();
            inf.readInt(1, 1000, "d_i_j");
            ensuref(usedColumns.insert(x).second,
                    "duplicate stone cell at row %d, column %d", i, x);
        }
        inf.readEoln();

        for (int used = 0; used <= m; ++used) {
            if (i >= 1) {
                for (bool prev : reachable[i - 1][used]) {
                    if (!prev) {
                        continue;
                    }
                    for (int j = 0; j < k; ++j) {
                        reachable[i][used][j] = true;
                    }
                    break;
                }
            }

            if (i >= 2 && used > 0) {
                for (bool prev : reachable[i - 2][used - 1]) {
                    if (!prev) {
                        continue;
                    }
                    for (int j = 0; j < k; ++j) {
                        reachable[i][used][j] = true;
                    }
                    break;
                }
            }
        }
    }

    bool canReachOppositeBank = false;
    for (int used = 0; used <= m; ++used) {
        for (bool prev : reachable[n][used]) {
            canReachOppositeBank = canReachOppositeBank || prev;
        }
        if (used > 0) {
            for (bool prev : reachable[n - 1][used - 1]) {
                canReachOppositeBank = canReachOppositeBank || prev;
            }
        }
    }
    ensuref(canReachOppositeBank, "opposite bank is unreachable");

    inf.readEof();
}
