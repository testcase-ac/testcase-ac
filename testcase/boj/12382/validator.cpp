#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "N");
        inf.readEoln();

        vector<vector<bool>> inherits(n + 1, vector<bool>(n + 1, false));
        for (int i = 1; i <= n; ++i) {
            int m = inf.readInt(0, 10, "M_i");
            vector<bool> seen(n + 1, false);

            for (int j = 0; j < m; ++j) {
                inf.readSpace();
                int parent = inf.readInt(1, n, "parent");

                ensuref(parent != i, "class %d inherits from itself", i);
                ensuref(!seen[parent],
                        "duplicate parent %d on class %d", parent, i);

                seen[parent] = true;
                inherits[i][parent] = true;
            }

            inf.readEoln();
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    inherits[i][j] = inherits[i][j] ||
                                     (inherits[i][k] && inherits[k][j]);
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            ensuref(!inherits[i][i],
                    "cycle detected through class %d", i);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                ensuref(!(inherits[i][j] && inherits[j][i]),
                        "classes %d and %d reach each other", i, j);
            }
        }
    }

    inf.readEof();
}
