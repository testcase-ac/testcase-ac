#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 7);

    int N = 0;
    vector<pair<int,int>> edges;
    vector< set<int> > adj;

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        if (u <= 0 || v <= 0 || u >= (int)adj.size() || v >= (int)adj.size()) return;
        if (adj[u].insert(v).second) {
            edges.push_back({u, v});
        }
    };

    auto buildSCC = [&](int L, int R, double pExtra) {
        int sz = R - L + 1;
        if (sz >= 2) {
            for (int i = L; i <= R; i++) {
                int j = (i == R ? L : i + 1);
                addEdge(i, j);
            }
        }
        if (pExtra > 0.0) {
            for (int u = L; u <= R; u++) {
                for (int v = L; v <= R; v++) {
                    if (u == v) continue;
                    if (rnd.next() < pExtra) addEdge(u, v);
                }
            }
        }
    };

    if (scenario == 0) {
        // Single node, no edges
        N = 1;
        // edges empty
    } else if (scenario == 1) {
        // Strongly connected, simple-ish SCC
        N = rnd.next(2, 9);
        adj.assign(N + 1, set<int>());
        double p = (rnd.next(0, 1) == 0 ? 0.0 : 0.2);
        buildSCC(1, N, p);
    } else if (scenario == 2) {
        // Strongly connected, denser SCC
        N = rnd.next(3, 9);
        adj.assign(N + 1, set<int>());
        double p = rnd.any(vector<double>{0.3, 0.6});
        buildSCC(1, N, p);
    } else if (scenario == 3) {
        // Directed chain (DAG), not strongly connected
        N = rnd.next(2, 9);
        adj.assign(N + 1, set<int>());
        for (int i = 1; i < N; i++) addEdge(i, i + 1);
        for (int u = 1; u <= N; u++) {
            for (int v = u + 2; v <= N; v++) {
                if (rnd.next() < 0.3) addEdge(u, v);
            }
        }
    } else if (scenario == 4) {
        // Two SCCs with one-way connections between them
        N = rnd.next(3, 9);
        adj.assign(N + 1, set<int>());
        int n1 = rnd.next(1, N - 1);
        int n2 = N - n1;
        buildSCC(1, n1, 0.3);
        buildSCC(n1 + 1, N, 0.3);

        bool firstToSecond = (rnd.next(0, 1) == 0);
        bool hasBridge = false;
        if (firstToSecond) {
            for (int u = 1; u <= n1; u++) {
                for (int v = n1 + 1; v <= N; v++) {
                    if (rnd.next() < 0.3) {
                        addEdge(u, v);
                        hasBridge = true;
                    }
                }
            }
            if (!hasBridge) addEdge(rnd.next(1, n1), rnd.next(n1 + 1, N));
        } else {
            for (int u = n1 + 1; u <= N; u++) {
                for (int v = 1; v <= n1; v++) {
                    if (rnd.next() < 0.3) {
                        addEdge(u, v);
                        hasBridge = true;
                    }
                }
            }
            if (!hasBridge) addEdge(rnd.next(n1 + 1, N), rnd.next(1, n1));
        }
    } else if (scenario == 5) {
        // Disconnected graph (no edges between components)
        N = rnd.next(2, 9);
        adj.assign(N + 1, set<int>());
        int n1 = (N == 2 ? 1 : rnd.next(1, N - 1));
        int n2 = N - n1;
        buildSCC(1, n1, 0.3);
        buildSCC(n1 + 1, N, 0.3);
        // No cross edges
    } else if (scenario == 6) {
        // Almost strongly connected but one vertex is unreachable from others
        N = rnd.next(3, 9);
        adj.assign(N + 1, set<int>());
        int special = N;
        buildSCC(1, N - 1, 0.4); // core 1..N-1 is strongly connected

        bool hasOut = false;
        for (int v = 1; v <= N - 1; v++) {
            if (rnd.next() < 0.5) {
                addEdge(special, v);
                hasOut = true;
            }
        }
        if (!hasOut) addEdge(special, rnd.next(1, N - 1));
        // No edges into 'special' to break strong connectivity
    } else { // scenario == 7
        // Random directed graph with moderate density
        N = rnd.next(2, 9);
        adj.assign(N + 1, set<int>());
        double p = rnd.any(vector<double>{0.15, 0.3, 0.5});
        for (int u = 1; u <= N; u++) {
            for (int v = 1; v <= N; v++) {
                if (u == v) continue;
                if (rnd.next() < p) addEdge(u, v);
            }
        }
        if (edges.empty()) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            while (v == u) v = rnd.next(1, N);
            addEdge(u, v);
        }
    }

    println(N, (int)edges.size());
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
