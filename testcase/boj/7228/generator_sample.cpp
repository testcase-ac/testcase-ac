#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int type;
};

static bool addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int type) {
    if (a == b || used.count({a, b})) return false;
    used.insert({a, b});
    edges.push_back({a, b, type});
    return true;
}

static void addRandomEdges(vector<Edge>& edges, set<pair<int, int>>& used, int n, int targetM) {
    int guard = 0;
    while ((int)edges.size() < targetM && guard < targetM * 100 + 200) {
        ++guard;
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a == b) continue;
        addEdge(edges, used, a, b, rnd.next(0, 1));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        vector<int> truth(n + 1);
        for (int i = 1; i <= n; ++i) truth[i] = rnd.next(0, 1);

        int targetM = rnd.next(n - 1, min(n * (n - 1), 35));
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            addEdge(edges, used, parent, i, truth[parent] ^ truth[i]);
        }
        addRandomEdges(edges, used, n, targetM);

        for (Edge& edge : edges) {
            edge.type = truth[edge.a] ^ truth[edge.b];
        }
    } else if (mode == 1) {
        n = max(n, 3);
        int k = rnd.next(3, min(n, 9));
        int parity = 0;
        for (int i = 1; i <= k; ++i) {
            int type = rnd.next(0, 1);
            parity ^= type;
            addEdge(edges, used, i, i % k + 1, type);
        }
        if (parity == 0) edges.back().type ^= 1;
        addRandomEdges(edges, used, n, rnd.next(k, min(n * (n - 1), 25)));
    } else if (mode == 2) {
        int targetM = rnd.next(1, min(n * (n - 1), 30));
        addRandomEdges(edges, used, n, targetM);
        for (Edge& edge : edges) edge.type = 1;
    } else if (mode == 3) {
        int pairs = rnd.next(1, min(n / 2 + 1, 6));
        for (int i = 0; i < pairs; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a == b) {
                --i;
                continue;
            }
            addEdge(edges, used, a, b, rnd.next(0, 1));
            addEdge(edges, used, b, a, rnd.next(0, 1));
        }
        addRandomEdges(edges, used, n, rnd.next((int)edges.size(), min(n * (n - 1), 24)));
    } else {
        int pathLen = rnd.next(2, n);
        for (int i = 1; i < pathLen; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(0, 1));
        }
        if (rnd.next(0, 1)) addEdge(edges, used, pathLen, 1, rnd.next(0, 1));
        addRandomEdges(edges, used, n, rnd.next((int)edges.size(), min(n * (n - 1), 28)));
    }

    if (edges.empty()) addEdge(edges, used, 1, 2, rnd.next(0, 1));
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.type);
    }

    return 0;
}
