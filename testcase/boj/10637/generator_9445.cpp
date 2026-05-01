#include "testlib.h"
using namespace std;

struct Edge {
    int a, b, w;
};

const int MAXN = 10;
const int MAXE = 20;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    bool used[MAXN + 1][MAXN + 1] = {};
    vector<Edge> edges;

    auto addEdge = [&](int a, int b, int w) {
        if (a == b) return;
        if (used[a][b]) return;
        used[a][b] = used[b][a] = true;
        Edge e{a, b, w};
        edges.push_back(e);
    };

    int n;
    int scenario = rnd.next(0, 5); // 6 scenarios: 0..5

    switch (scenario) {
        case 0: { // pure tree (connected, all removals disconnect)
            n = rnd.next(2, 6);
            for (int i = 2; i <= n; ++i) {
                int p = rnd.next(1, i - 1);
                int w = rnd.next(0, 20);
                addEdge(p, i, w);
            }
            break;
        }
        case 1: { // tree + one extra edge (single extra cycle)
            n = rnd.next(3, 8);
            for (int i = 2; i <= n; ++i) {
                int p = rnd.next(1, i - 1);
                int w = rnd.next(0, 20);
                addEdge(p, i, w);
            }
            // choose one non-existing edge
            vector<pair<int,int>> cand;
            for (int i = 1; i <= n; ++i)
                for (int j = i + 1; j <= n; ++j)
                    if (!used[i][j])
                        cand.push_back(make_pair(i, j));
            if (!cand.empty() && (int)edges.size() < MAXE) {
                pair<int,int> e = rnd.any(cand);
                int w;
                if (rnd.next(0, 1) == 0)
                    w = rnd.next(0, 5);      // possibly joins MST
                else
                    w = rnd.next(10, 30);    // likely outside MST
                addEdge(e.first, e.second, w);
            }
            break;
        }
        case 2: { // connected, relatively dense graph
            n = rnd.next(4, 8);
            // base tree to ensure connectivity
            for (int i = 2; i <= n; ++i) {
                int p = rnd.next(1, i - 1);
                int w = rnd.next(0, 40);
                addEdge(p, i, w);
            }
            // extra edges with some density
            double dens;
            int t = rnd.next(0, 2);
            if (t == 0) dens = 0.3;
            else if (t == 1) dens = 0.6;
            else dens = 1.0;
            for (int i = 1; i <= n && (int)edges.size() < MAXE; ++i) {
                for (int j = i + 1; j <= n && (int)edges.size() < MAXE; ++j) {
                    if (used[i][j]) continue;
                    if (rnd.next() < dens) {
                        int w = rnd.next(0, 50);
                        addEdge(i, j, w);
                    }
                }
            }
            break;
        }
        case 3: { // disconnected graph (no spanning tree overall)
            n = rnd.next(4, 9);
            int comps = rnd.next(2, min(3, n)); // 2 or 3 components

            vector<int> nodes;
            for (int i = 1; i <= n; ++i) nodes.push_back(i);
            shuffle(nodes.begin(), nodes.end());

            vector<int> compSize(comps, 1);
            int remaining = n - comps;
            for (int i = 0; i < remaining; ++i) {
                int c = rnd.next(0, comps - 1);
                compSize[c]++;
            }

            int idx = 0;
            for (int c = 0; c < comps; ++c) {
                vector<int> compNodes;
                for (int k = 0; k < compSize[c]; ++k) {
                    compNodes.push_back(nodes[idx++]);
                }
                int sz = (int)compNodes.size();
                if (sz >= 2) {
                    // tree inside component
                    for (int i = 1; i < sz; ++i) {
                        int p = rnd.next(0, i - 1);
                        int u = compNodes[p];
                        int v = compNodes[i];
                        int w = rnd.next(1, 30);
                        addEdge(u, v, w);
                    }
                    // optional extra edges inside component
                    for (int i = 0; i < sz && (int)edges.size() < MAXE; ++i) {
                        for (int j = i + 1; j < sz && (int)edges.size() < MAXE; ++j) {
                            int u = compNodes[i];
                            int v = compNodes[j];
                            if (used[u][v]) continue;
                            if (rnd.next() < 0.3) {
                                int w = rnd.next(1, 40);
                                addEdge(u, v, w);
                            }
                        }
                    }
                }
            }
            break;
        }
        case 4: { // equal weights everywhere
            n = rnd.next(3, 8);
            int baseWeights[4] = {0, 1, 5, 10};
            int w0 = baseWeights[rnd.next(0, 3)];
            // base tree
            for (int i = 2; i <= n; ++i) {
                int p = rnd.next(1, i - 1);
                addEdge(p, i, w0);
            }
            // add more edges, same weight
            for (int i = 1; i <= n && (int)edges.size() < MAXE; ++i) {
                for (int j = i + 1; j <= n && (int)edges.size() < MAXE; ++j) {
                    if (used[i][j]) continue;
                    if (rnd.next() < 0.5) {
                        addEdge(i, j, w0);
                    }
                }
            }
            break;
        }
        case 5: { // mix of zero and very large weights
            n = rnd.next(3, 8);
            // base tree
            for (int i = 2; i <= n; ++i) {
                int p = rnd.next(1, i - 1);
                double r = rnd.next();
                int w;
                if (r < 0.4) w = 0;
                else if (r < 0.8) w = rnd.next(1, 10);
                else w = rnd.next(900000, 1000000);
                addEdge(p, i, w);
            }
            // extra edges
            for (int i = 1; i <= n && (int)edges.size() < MAXE; ++i) {
                for (int j = i + 1; j <= n && (int)edges.size() < MAXE; ++j) {
                    if (used[i][j]) continue;
                    if (rnd.next() < 0.4) {
                        int w;
                        if (rnd.next(0, 1) == 0) w = 0;
                        else w = 1000000;
                        addEdge(i, j, w);
                    }
                }
            }
            break;
        }
    }

    // Shuffle edge order
    shuffle(edges.begin(), edges.end());
    int m = (int)edges.size();

    println(n, m);
    for (int i = 0; i < m; ++i)
        println(edges[i].a, edges[i].b, edges[i].w);

    return 0;
}
