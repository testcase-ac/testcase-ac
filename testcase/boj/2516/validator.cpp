#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    vector<vector<int>> enemies(n + 1);
    for (int i = 1; i <= n; ++i) {
        int m = inf.readInt(0, 3, "M");
        enemies[i].reserve(m);
        for (int j = 0; j < m; ++j) {
            inf.readSpace();
            int x = inf.readInt(1, n, "enemy");
            ensuref(x != i, "monkey %d lists itself as an enemy", i);
            if (j > 0) {
                ensuref(enemies[i][j - 1] < x,
                        "enemy list for monkey %d is not strictly increasing", i);
            }
            enemies[i].push_back(x);
        }
        inf.readEoln();
    }

    for (int i = 1; i <= n; ++i) {
        for (int x : enemies[i]) {
            ensuref(binary_search(enemies[x].begin(), enemies[x].end(), i),
                    "enemy relationship between %d and %d is not symmetric", i, x);
        }
    }

    inf.readEof();
}
