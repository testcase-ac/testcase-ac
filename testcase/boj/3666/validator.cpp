#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(1, 100, "n");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 0, 100, "a_i");
        inf.readEoln();

        // Check at least one territory is owned by you, and at least one by enemy
        int cnt_own = 0, cnt_enemy = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] > 0) cnt_own++;
            else cnt_enemy++;
        }
        ensuref(cnt_own >= 1, "At least one territory must be owned by you (a_i > 0)");
        ensuref(cnt_enemy >= 1, "At least one territory must be owned by enemy (a_i == 0)");

        // Read adjacency matrix
        vector<string> adj(n);
        for (int i = 0; i < n; ++i) {
            adj[i] = inf.readLine("[YN]{"+to_string(n)+","+to_string(n)+"}", "adjacency row");
            ensuref((int)adj[i].size() == n, "Adjacency row %d must have length %d", i+1, n);
            for (int j = 0; j < n; ++j) {
                ensuref(adj[i][j] == 'Y' || adj[i][j] == 'N', "Adjacency matrix must contain only 'Y' or 'N' at (%d,%d)", i+1, j+1);
            }
        }

        // Check symmetry and diagonal
        for (int i = 0; i < n; ++i) {
            ensuref(adj[i][i] == 'N', "Adjacency matrix diagonal (%d,%d) must be 'N'", i+1, i+1);
            for (int j = 0; j < n; ++j) {
                ensuref(adj[i][j] == adj[j][i], "Adjacency matrix must be symmetric at (%d,%d) and (%d,%d)", i+1, j+1, j+1, i+1);
            }
        }

        // Check at least one of your territory is adjacent to at least one enemy territory
        bool found_adj = false;
        for (int i = 0; i < n; ++i) {
            if (a[i] > 0) {
                for (int j = 0; j < n; ++j) {
                    if (a[j] == 0 && adj[i][j] == 'Y') {
                        found_adj = true;
                        break;
                    }
                }
                if (found_adj) break;
            }
        }
        ensuref(found_adj, "At least one of your territories must be adjacent to at least one enemy territory");

        // Each test case must end with exactly one newline (already consumed by readLine)
    }

    inf.readEof();
}
