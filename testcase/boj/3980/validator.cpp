#include "testlib.h"
#include <vector>
using namespace std;

// DFS for finding augmenting path in bipartite matching
bool dfs_match(int u, const vector<vector<int>>& adj, vector<char>& seen, vector<int>& matchR) {
    for (int v : adj[u]) {
        if (seen[v]) continue;
        seen[v] = 1;
        if (matchR[v] < 0 || dfs_match(matchR[v], adj, seen, matchR)) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases C
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    for (int tc = 1; tc <= C; tc++) {
        setTestCase(tc);

        // Read the 11x11 ability matrix s[i][j]
        // s[i][j] in [0,100], and for each player i, count of s[i][j] > 0 is in [1,5]
        vector<vector<int>> s(11, vector<int>(11));
        vector<vector<int>> adj(11);
        for (int i = 0; i < 11; i++) {
            // read exactly 11 ints
            vector<int> row = inf.readInts(11, 0, 100, "s_ij");
            inf.readEoln();
            int positive_count = 0;
            for (int j = 0; j < 11; j++) {
                s[i][j] = row[j];
                if (s[i][j] > 0) {
                    positive_count++;
                    adj[i].push_back(j);
                }
            }
            ensuref(positive_count >= 1,
                    "Player %d in case %d has no valid positions (all zeros)", i+1, tc);
            ensuref(positive_count <= 5,
                    "Player %d in case %d has more than 5 valid positions (%d)", i+1, tc, positive_count);
        }

        // Now check that there exists a perfect matching of size 11
        // between players (u=0..10) and positions (v=0..10).
        vector<int> matchR(11, -1);
        int match_count = 0;
        for (int u = 0; u < 11; u++) {
            vector<char> seen(11, 0);
            if (dfs_match(u, adj, seen, matchR)) {
                match_count++;
            }
        }
        ensuref(match_count == 11,
                "No perfect matching exists in case %d: only %d matched", tc, match_count);
    }

    inf.readEof();
    return 0;
}
