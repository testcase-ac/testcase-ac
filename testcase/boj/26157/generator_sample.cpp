#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, int u, int v) {
    if (u != v) edges.push_back({u, v});
}

void addCycle(vector<Edge>& edges, const vector<int>& nodes) {
    if (nodes.size() < 2) return;
    for (int i = 0; i < int(nodes.size()); ++i) {
        addEdge(edges, nodes[i], nodes[(i + 1) % nodes.size()]);
    }
}

vector<vector<int>> partitionNodes(int n, int parts) {
    vector<vector<int>> groups(parts);
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) nodes.push_back(i);
    shuffle(nodes.begin(), nodes.end());

    for (int i = 0; i < parts; ++i) groups[i].push_back(nodes[i]);
    for (int i = parts; i < n; ++i) groups[rnd.next(parts)].push_back(nodes[i]);
    return groups;
}

void addInternalEdges(vector<Edge>& edges, const vector<int>& group) {
    addCycle(edges, group);
    for (int u : group) {
        for (int v : group) {
            if (u != v && rnd.next(4) == 0) addEdge(edges, u, v);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = mode == 0 ? rnd.next(1, 3) : rnd.next(2, 14);
    vector<Edge> edges;

    if (mode == 0) {
        if (n > 1 && rnd.next(2)) addEdge(edges, 1, 2);
    } else if (mode == 1) {
        vector<int> nodes;
        for (int i = 1; i <= n; ++i) nodes.push_back(i);
        addInternalEdges(edges, nodes);
    } else {
        int parts = rnd.next(2, min(n, 6));
        vector<vector<int>> groups = partitionNodes(n, parts);

        for (const auto& group : groups) addInternalEdges(edges, group);

        if (mode == 2) {
            for (int i = 0; i + 1 < parts; ++i) {
                addEdge(edges, rnd.any(groups[i]), rnd.any(groups[i + 1]));
                if (rnd.next(3) == 0) addEdge(edges, rnd.any(groups[i]), rnd.any(groups[i + 1]));
            }
        } else if (mode == 3) {
            for (int i = 1; i < parts; ++i) {
                addEdge(edges, rnd.any(groups[0]), rnd.any(groups[i]));
            }
        } else if (mode == 4) {
            for (int i = 2; i < parts; ++i) {
                addEdge(edges, rnd.any(groups[0]), rnd.any(groups[i]));
                addEdge(edges, rnd.any(groups[1]), rnd.any(groups[i]));
            }
        } else {
            for (int i = 0; i < parts; ++i) {
                for (int j = i + 1; j < parts; ++j) {
                    if (rnd.next(2)) addEdge(edges, rnd.any(groups[i]), rnd.any(groups[j]));
                    else addEdge(edges, rnd.any(groups[j]), rnd.any(groups[i]));
                }
            }
        }
    }

    int extraDuplicates = rnd.next(0, min(8, int(edges.size())));
    for (int i = 0; i < extraDuplicates; ++i) edges.push_back(rnd.any(edges));
    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
