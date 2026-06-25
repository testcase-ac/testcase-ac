#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(set<Edge>& used, vector<Edge>& edges, int a, int b) {
    if (a == b) return;
    Edge edge = minmax(a, b);
    if (used.insert(edge).second) {
        edges.push_back(edge);
    }
}

void addRandomEdges(set<Edge>& used, vector<Edge>& edges, int n, int targetM) {
    vector<Edge> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!used.count({i, j})) {
                candidates.push_back({i, j});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    for (Edge edge : candidates) {
        if ((int)edges.size() >= targetM) break;
        addEdge(used, edges, edge.first, edge.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int maxM = n * (n - 1) / 2;
    set<Edge> used;
    vector<Edge> edges;

    if (mode == 0) {
        int components = rnd.next(1, min(n, 4));
        for (int v = components + 1; v <= n; ++v) {
            addEdge(used, edges, v, rnd.next(1, v - 1));
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        if (n >= 3) {
            addEdge(used, edges, 1, rnd.next(3, n));
        }
    } else if (mode == 2) {
        int targetM = rnd.next(1, min(maxM, n + rnd.next(0, n / 2)));
        addRandomEdges(used, edges, n, targetM);
    } else if (mode == 3) {
        int leftSize = rnd.next(1, n - 1);
        vector<Edge> candidates;
        for (int a = 1; a <= leftSize; ++a) {
            for (int b = leftSize + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }

        shuffle(candidates.begin(), candidates.end());
        int targetM = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < targetM; ++i) {
            addEdge(used, edges, candidates[i].first, candidates[i].second);
        }
    } else {
        int targetM = rnd.next(max(1, maxM / 2), maxM);
        addRandomEdges(used, edges, n, targetM);
    }

    if (edges.empty()) {
        addEdge(used, edges, 1, 2);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (Edge edge : edges) {
        int a = label[edge.first];
        int b = label[edge.second];
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }

    return 0;
}
