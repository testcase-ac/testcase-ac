#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

void addEdge(Graph& graph, int child, int parent) {
    if (child == parent) return;
    auto& parents = graph[child];
    if (parents.size() >= 10) return;
    if (find(parents.begin(), parents.end(), parent) == parents.end()) {
        parents.push_back(parent);
    }
}

Graph makeChain(int n) {
    Graph graph(n + 1);
    for (int i = 1; i < n; ++i) {
        addEdge(graph, i, i + 1);
    }
    return graph;
}

Graph makeDiamond(int n) {
    Graph graph(n + 1);
    int root = rnd.next(1, max(1, n - 3));
    int left = root + 1;
    int right = root + 2;
    int top = root + 3;

    addEdge(graph, root, left);
    addEdge(graph, root, right);
    addEdge(graph, left, top);
    addEdge(graph, right, top);

    for (int i = 1; i <= n; ++i) {
        int extra = rnd.next(0, min(2, n - i));
        for (int tries = 0; tries < extra * 3; ++tries) {
            int parent = rnd.next(i + 1, n);
            addEdge(graph, i, parent);
            if ((int)graph[i].size() >= extra) break;
        }
    }
    return graph;
}

Graph makeWideClass(int n) {
    Graph graph(n + 1);
    int m = min(10, n - 1);
    for (int parent = 2; parent <= m + 1; ++parent) {
        addEdge(graph, 1, parent);
    }
    return graph;
}

Graph makeRandomDag(int n, bool sparse) {
    Graph graph(n + 1);
    int maxParents = sparse ? 2 : min(10, max(1, n / 2));

    for (int child = 1; child <= n; ++child) {
        int available = n - child;
        int limit = min(maxParents, available);
        int m = limit == 0 ? 0 : rnd.next(0, limit);
        set<int> chosen;
        while ((int)chosen.size() < m) {
            chosen.insert(rnd.next(child + 1, n));
        }
        for (int parent : chosen) {
            addEdge(graph, child, parent);
        }
    }
    return graph;
}

void printGraph(const Graph& graph) {
    int n = (int)graph.size() - 1;
    println(n);
    for (int i = 1; i <= n; ++i) {
        vector<int> parents = graph[i];
        shuffle(parents.begin(), parents.end());
        printf("%d", (int)parents.size());
        for (int parent : parents) {
            printf(" %d", parent);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n = mode == 2 ? rnd.next(11, 18) : rnd.next(1, 14);

        Graph graph;
        if (mode == 0 && n >= 4) {
            graph = makeDiamond(n);
        } else if (mode == 1) {
            graph = makeChain(n);
        } else if (mode == 2) {
            graph = makeWideClass(n);
        } else {
            graph = makeRandomDag(n, mode == 3);
        }

        printGraph(graph);
    }

    return 0;
}
