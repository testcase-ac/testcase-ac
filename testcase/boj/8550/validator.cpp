#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    set<pair<int, int>> playedPairs;

    for (int i = 1; i <= m; ++i) {
        int winner = inf.readInt(1, n, "winner");
        inf.readSpace();
        int loser = inf.readInt(1, n, "loser");
        inf.readEoln();

        ensuref(winner != loser, "match %d has the same winner and loser: %d", i, winner);

        auto pairKey = minmax(winner, loser);
        ensuref(playedPairs.insert(pairKey).second,
                "players %d and %d appear in more than one match by match %d",
                pairKey.first, pairKey.second, i);

        graph[winner].push_back(loser);
        ++indegree[loser];
    }

    queue<int> q;
    for (int player = 1; player <= n; ++player) {
        if (indegree[player] == 0) {
            q.push(player);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int player = q.front();
        q.pop();
        ++visited;

        for (int next : graph[player]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    ensuref(visited == n, "match results must allow at least one valid ranking");

    inf.readEof();
}
