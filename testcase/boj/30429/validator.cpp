#include "testlib.h"

#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int claimAlien = inf.readInt(0, 1, "claim_i");
        inf.readEoln();

        // CHECK: The prose says each person was asked about another person, but
        // the formal bounds allow N = 1 and do not state A_i != i.
        graph[i].push_back({a, claimAlien});
        graph[a].push_back({i, claimAlien});
    }
    inf.readEof();

    vector<int> alien(n + 1, -1);
    for (int start = 1; start <= n; ++start) {
        if (alien[start] != -1) {
            continue;
        }

        alien[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto [v, xorValue] : graph[u]) {
                int expected = alien[u] ^ xorValue;
                if (alien[v] == -1) {
                    alien[v] = expected;
                    q.push(v);
                } else {
                    ensuref(alien[v] == expected,
                            "inconsistent testimonies involving people %d and %d",
                            u, v);
                }
            }
        }
    }
}
