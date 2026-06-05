#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<pair<int, int>>& edges, int u, int v) {
    if (u != v) {
        edges.push_back({u, v});
    }
}

vector<pair<int, int>> makeCycle(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        addEdge(edges, i, i == n ? 1 : i + 1);
    }
    return edges;
}

vector<pair<int, int>> makeChain(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1);
    }
    return edges;
}

vector<pair<int, int>> makeComponentGraph(int n) {
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    int groupCount = rnd.next(2, min(n, 5));
    vector<vector<int>> groups(groupCount);
    for (int i = 0; i < n; ++i) {
        groups[i % groupCount].push_back(nodes[i]);
    }

    vector<pair<int, int>> edges;
    for (const auto& group : groups) {
        if (group.size() == 1) {
            continue;
        }
        for (int i = 0; i < (int)group.size(); ++i) {
            addEdge(edges, group[i], group[(i + 1) % group.size()]);
        }
    }

    for (int i = 0; i + 1 < groupCount; ++i) {
        addEdge(edges, rnd.any(groups[i]), rnd.any(groups[i + 1]));
        if (rnd.next(0, 2) == 0 && i + 2 < groupCount) {
            addEdge(edges, rnd.any(groups[i]), rnd.any(groups[i + 2]));
        }
    }

    return edges;
}

vector<pair<int, int>> makeRandomGraph(int n, bool dense) {
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (u != v) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxEdges = min<int>(candidates.size(), dense ? rnd.next(n, min<int>(candidates.size(), 3 * n)) : rnd.next(0, n + 2));
    candidates.resize(maxEdges);
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 16);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int n = rnd.next(1, 12);
        vector<pair<int, int>> edges;

        if (mode == 0) {
            n = rnd.next(1, 10);
        } else if (mode == 1) {
            n = rnd.next(2, 12);
            edges = makeCycle(n);
        } else if (mode == 2) {
            n = rnd.next(2, 12);
            edges = makeChain(n);
        } else if (mode == 3) {
            n = rnd.next(3, 12);
            edges = makeComponentGraph(n);
        } else {
            n = rnd.next(2, 12);
            edges = makeRandomGraph(n, rnd.next(0, 1) == 1);
        }

        shuffle(edges.begin(), edges.end());

        if (!edges.empty() && rnd.next(0, 4) == 0) {
            int duplicateCount = rnd.next(1, min<int>(3, edges.size()));
            for (int i = 0; i < duplicateCount; ++i) {
                edges.push_back(rnd.any(edges));
            }
            shuffle(edges.begin(), edges.end());
        }

        println(n, (int)edges.size());
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
