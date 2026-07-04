#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int length;
};

void addEdge(vector<Edge>& edges, int from, int to, int length) {
    edges.push_back({from, to, length});
}

vector<int> shuffledLabels(int n, int s, int f) {
    vector<int> middle;
    for (int v = 1; v <= n; ++v) {
        if (v == s || v == f) {
            continue;
        }
        middle.push_back(v);
    }
    shuffle(middle.begin(), middle.end());

    vector<int> label(n + 1);
    label[1] = s;
    label[n] = f;
    for (int i = 0; i < (int)middle.size(); ++i) {
        label[i + 2] = middle[i];
    }
    return label;
}

vector<Edge> relabelEdges(const vector<Edge>& edges, const vector<int>& label) {
    vector<Edge> result;
    for (const Edge& edge : edges) {
        result.push_back({label[edge.from], label[edge.to], edge.length});
    }
    shuffle(result.begin(), result.end());
    return result;
}

vector<Edge> makeLayeredCase(int n) {
    vector<Edge> edges;
    int split = rnd.next(2, n - 1);

    addEdge(edges, 1, split, rnd.next(1, 4));
    addEdge(edges, split, n, rnd.next(1, 4));

    int directLength = edges[0].length + edges[1].length + rnd.next(0, 1);
    addEdge(edges, 1, n, directLength);

    for (int v = 2; v < n; ++v) {
        if (v == split) {
            continue;
        }
        int first = rnd.next(1, 5);
        int extra = rnd.next(0, 2);
        addEdge(edges, 1, v, first);
        addEdge(edges, v, n, first + extra);
    }

    if (rnd.next(2) == 0) {
        addEdge(edges, 1, split, edges[0].length);
    }
    return edges;
}

vector<Edge> makeChainDetourCase(int n) {
    vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        addEdge(edges, v, v + 1, rnd.next(1, 3));
    }

    for (int v = 1; v + 2 <= n; ++v) {
        int chainLength = edges[v - 1].length + edges[v].length;
        addEdge(edges, v, v + 2, chainLength + rnd.next(0, 1));
    }

    int noise = rnd.next(0, n);
    for (int i = 0; i < noise; ++i) {
        int from = rnd.next(2, n);
        int to = rnd.next(1, from - 1);
        addEdge(edges, from, to, rnd.next(6, 12));
    }

    return edges;
}

vector<Edge> makeRandomDagCase(int n) {
    vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        addEdge(edges, v, v + 1, rnd.next(1, 4));
    }

    set<pair<int, int>> used;
    for (const Edge& edge : edges) {
        used.insert({edge.from, edge.to});
    }

    double density = rnd.next(0.20, 0.55);
    for (int from = 1; from <= n; ++from) {
        for (int to = from + 1; to <= n; ++to) {
            if (used.count({from, to}) || rnd.next() > density) {
                continue;
            }
            addEdge(edges, from, to, rnd.next(1, 8));
            if (rnd.next(5) == 0) {
                addEdge(edges, from, to, rnd.next(1, 8));
            }
        }
    }

    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(3, 8);
    vector<tuple<int, vector<Edge>, int, int>> cases;

    for (int tc = 0; tc < testCases; ++tc) {
        int n = rnd.next(3, 10);
        int mode = rnd.next(3);
        vector<Edge> edges;
        if (mode == 0) {
            edges = makeLayeredCase(n);
        } else if (mode == 1) {
            edges = makeChainDetourCase(n);
        } else {
            edges = makeRandomDagCase(n);
        }

        int s = rnd.next(1, n);
        int f = rnd.next(1, n - 1);
        if (f >= s) {
            ++f;
        }

        vector<int> label = shuffledLabels(n, s, f);
        edges = relabelEdges(edges, label);
        cases.push_back({n, edges, s, f});
    }

    println(testCases);
    for (const auto& [n, edges, s, f] : cases) {
        println(n, (int)edges.size());
        for (const Edge& edge : edges) {
            println(edge.from, edge.to, edge.length);
        }
        println(s, f);
    }

    return 0;
}
