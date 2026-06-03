#include "testlib.h"

#include <algorithm>
#include <array>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<array<bool, 13>, 13> graph{};
    vector<int> degree(13, 0);
    set<pair<int, int>> edges;

    for (int i = 1; i <= 12; ++i) {
        int x = inf.readInt(1, 12, "x");
        inf.readSpace();
        int y = inf.readInt(1, 12, "y");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d %d", i, x, y);
        auto edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, x, y);

        graph[x][y] = graph[y][x] = true;
        ++degree[x];
        ++degree[y];
    }

    inf.readEof();

    array<array<bool, 13>, 13> spica{};
    vector<pair<int, int>> templateEdges = {
        {1, 2},  {2, 3},  {3, 4},   {4, 5},
        {3, 7},  {4, 9},  {6, 7},   {7, 8},
        {8, 9},  {9, 10}, {10, 11}, {11, 12},
    };
    vector<int> templateDegree(13, 0);
    for (auto [u, v] : templateEdges) {
        spica[u][v] = spica[v][u] = true;
        ++templateDegree[u];
        ++templateDegree[v];
    }

    vector<int> order(12);
    for (int i = 0; i < 12; ++i) {
        order[i] = i + 1;
    }
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (degree[a] != degree[b]) {
            return degree[a] > degree[b];
        }
        return a < b;
    });

    vector<int> mapping(13, 0), used(13, 0);
    auto dfs = [&](auto&& self, int pos) -> bool {
        if (pos == 12) {
            return true;
        }

        int u = order[pos];
        for (int t = 1; t <= 12; ++t) {
            if (used[t] || degree[u] != templateDegree[t]) {
                continue;
            }

            bool ok = true;
            for (int i = 0; i < pos; ++i) {
                int v = order[i];
                if (graph[u][v] != spica[t][mapping[v]]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }

            mapping[u] = t;
            used[t] = true;
            if (self(self, pos + 1)) {
                return true;
            }
            used[t] = false;
            mapping[u] = 0;
        }
        return false;
    };

    ensuref(dfs(dfs, 0), "graph is not isomorphic to the Spica figure");
}
