#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, set<Edge>& seen, int from, int to) {
    if (seen.insert({from, to}).second) {
        edges.push_back({from, to});
    }
}

void addCycle(vector<Edge>& edges, set<Edge>& seen, const vector<int>& nodes) {
    if ((int)nodes.size() == 1) {
        if (rnd.next(2)) addEdge(edges, seen, nodes[0], nodes[0]);
        return;
    }
    for (int i = 0; i < (int)nodes.size(); ++i) {
        addEdge(edges, seen, nodes[i], nodes[(i + 1) % nodes.size()]);
    }
}

vector<int> shuffledLabels(int n) {
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin() + 1, p.end());
    return p;
}

void relabel(vector<Edge>& edges, const vector<int>& p) {
    for (auto& [from, to] : edges) {
        from = p[from];
        to = p[to];
    }
}

vector<vector<int>> partitionNodes(int n, int groups) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<vector<int>> parts(groups);
    for (int i = 0; i < groups; ++i) {
        parts[i].push_back(order[i]);
    }
    for (int i = groups; i < n; ++i) {
        parts[rnd.next(0, groups - 1)].push_back(order[i]);
    }
    return parts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(3, 8);
    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 5);
        int n = (mode == 0 ? rnd.next(1, 10) : rnd.next(2, 14));
        vector<Edge> edges;
        set<Edge> seen;

        if (mode == 0) {
            for (int v = 1; v <= n; ++v) {
                if (rnd.next(4) == 0) addEdge(edges, seen, v, v);
            }
        } else if (mode == 1) {
            double density = rnd.next(0.15, 0.45);
            for (int from = 1; from <= n; ++from) {
                for (int to = from + 1; to <= n; ++to) {
                    if (rnd.next() < density) addEdge(edges, seen, from, to);
                }
            }
        } else if (mode == 2) {
            int sinkSize = rnd.next(1, min(5, n));
            vector<int> sink;
            for (int v = n - sinkSize + 1; v <= n; ++v) sink.push_back(v);
            addCycle(edges, seen, sink);

            for (int v = 1; v <= n - sinkSize; ++v) {
                int to = rnd.next(v + 1, n);
                addEdge(edges, seen, v, to);
                if (rnd.next(3) == 0) addEdge(edges, seen, v, rnd.any(sink));
            }
        } else if (mode == 3) {
            int terminals = rnd.next(2, min(4, n));
            int prefix = rnd.next(0, n - terminals);
            for (int v = 1; v <= prefix; ++v) {
                addEdge(edges, seen, v, rnd.next(prefix + 1, n));
            }
            for (int v = prefix + 1; v <= n; ++v) {
                if (rnd.next(3) == 0) addEdge(edges, seen, v, v);
            }
        } else if (mode == 4) {
            int groups = rnd.next(2, min(5, n));
            vector<vector<int>> parts = partitionNodes(n, groups);
            for (auto& part : parts) addCycle(edges, seen, part);
            for (int i = 0; i + 1 < groups; ++i) {
                addEdge(edges, seen, rnd.any(parts[i]), rnd.any(parts[i + 1]));
                if (rnd.next(2)) addEdge(edges, seen, rnd.any(parts[i]), rnd.any(parts[i + 1]));
            }
        } else {
            double density = rnd.next(0.05, 0.25);
            for (int from = 1; from <= n; ++from) {
                for (int to = 1; to <= n; ++to) {
                    if (rnd.next() < density) addEdge(edges, seen, from, to);
                }
            }
            if (edges.empty()) addEdge(edges, seen, rnd.next(1, n), rnd.next(1, n));
        }

        relabel(edges, shuffledLabels(n));
        shuffle(edges.begin(), edges.end());

        println(n, (int)edges.size());
        for (auto [from, to] : edges) {
            println(from, to);
        }
    }

    println(0);
    return 0;
}
