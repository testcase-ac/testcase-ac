#include "testlib.h"
using namespace std;

struct Edge {
    int a, b, c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int Mlimit = 35;

    int scenario = rnd.next(0, 9); // 10 different scenarios: 0..9

    int N = 0;
    vector<int> P;
    vector<Edge> edges;
    bool used[16][16] = {false};

    auto addEdgeUnique = [&](int u, int v, int c) {
        if (u == v) return;
        if (u > v) swap(u, v);
        if (!used[u][v]) {
            used[u][v] = used[v][u] = true;
            edges.push_back({u, v, c});
        }
    };

    switch (scenario) {
        case 0: {
            // Single node, no edges
            N = 1;
            P.resize(N);
            P[0] = rnd.next(0, 10); // small cost
            // edges empty
            break;
        }
        case 1: {
            // Very small, quite dense
            N = rnd.next(2, 4);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                P[i] = rnd.next(0, 10);
            }
            for (int u = 1; u <= N; ++u) {
                for (int v = u + 1; v <= N; ++v) {
                    if (rnd.next(0, 99) < 70) {
                        int c = rnd.next(0, 10);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            break;
        }
        case 2: {
            // Tree structure
            N = rnd.next(5, 8);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 99) < 20) P[i] = 0;
                else P[i] = rnd.next(1, 10);
            }
            for (int v = 2; v <= N; ++v) {
                int u = rnd.next(1, v - 1);
                int c = rnd.next(1, 10); // positive edges
                addEdgeUnique(u, v, c);
            }
            break;
        }
        case 3: {
            // Random sparse graph
            N = rnd.next(7, 12);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                P[i] = rnd.next(0, 20);
            }
            for (int u = 1; u <= N; ++u) {
                for (int v = u + 1; v <= N; ++v) {
                    if (rnd.next(0, 99) < 30) {
                        int c = rnd.next(0, 20);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            break;
        }
        case 4: {
            // Densish graph, possibly higher edge weights
            N = rnd.next(7, 12);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0)
                    P[i] = rnd.next(0, 20);
                else
                    P[i] = rnd.next(30, 100);
            }
            bool highC = (rnd.next(0, 1) == 0);
            for (int u = 1; u <= N; ++u) {
                for (int v = u + 1; v <= N; ++v) {
                    if (rnd.next(0, 99) < 65) {
                        int c;
                        if (highC) c = rnd.next(50, 100);
                        else c = rnd.next(0, 30);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            break;
        }
        case 5: {
            // Chain + some chords
            N = rnd.next(5, 10);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                P[i] = rnd.next(0, 15);
            }
            // Path edges
            for (int i = 1; i < N; ++i) {
                int c = rnd.next(1, 15);
                addEdgeUnique(i, i + 1, c);
            }
            // Extra chords
            for (int k = 0; k < N; ++k) {
                if (rnd.next(0, 99) < 40) {
                    int u = rnd.next(1, N);
                    int v = rnd.next(1, N);
                    if (u != v) {
                        int c = rnd.next(0, 20);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            break;
        }
        case 6: {
            // Two clusters, dense inside, sparse between
            N = rnd.next(8, 15);
            P.resize(N);
            int mid = rnd.next(3, N - 3); // split position
            for (int i = 0; i < N; ++i) {
                if (i < mid)
                    P[i] = rnd.next(0, 10);    // cheaper cluster
                else
                    P[i] = rnd.next(5, 20);    // more expensive
            }
            // Left cluster
            for (int u = 1; u <= mid; ++u) {
                for (int v = u + 1; v <= mid; ++v) {
                    if (rnd.next(0, 99) < 60) {
                        int c = rnd.next(0, 25);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            // Right cluster
            for (int u = mid + 1; u <= N; ++u) {
                for (int v = u + 1; v <= N; ++v) {
                    if (rnd.next(0, 99) < 60) {
                        int c = rnd.next(0, 25);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            // Between clusters
            for (int u = 1; u <= mid; ++u) {
                for (int v = mid + 1; v <= N; ++v) {
                    if (rnd.next(0, 99) < 20) {
                        int c = rnd.next(0, 30);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            break;
        }
        case 7: {
            // No edges, costs mostly positive -> best is empty set (0)
            N = rnd.next(3, 10);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                P[i] = rnd.next(5, 15);
            }
            // edges remain empty
            break;
        }
        case 8: {
            // Hand-crafted tricky small instances
            int pattern = rnd.next(0, 1);
            if (pattern == 0) {
                // Best is empty set (all subsets negative)
                N = 3;
                P = {5, 5, 5};
                edges.push_back({1, 2, 3});
                edges.push_back({2, 3, 3});
                edges.push_back({1, 3, 3});
            } else {
                // Best is some non-trivial subset
                N = 4;
                P = {8, 1, 1, 8};
                edges.push_back({1, 2, 10});
                edges.push_back({2, 3, 1});
                edges.push_back({3, 4, 10});
            }
            break;
        }
        case 9: {
            // Graph with some duplicate edges between same pair
            N = rnd.next(4, 8);
            P.resize(N);
            for (int i = 0; i < N; ++i) {
                P[i] = rnd.next(0, 20);
            }
            // Generate a moderate number of unique edges
            for (int u = 1; u <= N; ++u) {
                for (int v = u + 1; v <= N; ++v) {
                    if ((int)edges.size() >= Mlimit - 3) break;
                    if (rnd.next(0, 99) < 40) {
                        int c = rnd.next(0, 25);
                        addEdgeUnique(u, v, c);
                    }
                }
            }
            // Ensure at least a couple of edges
            if (edges.size() < 2) {
                for (int u = 1; u < N && (int)edges.size() < 2; ++u) {
                    int v = u + 1;
                    int c = rnd.next(0, 25);
                    addEdgeUnique(u, v, c);
                }
            }
            // Add duplicates of some existing edges
            int dupCnt = rnd.next(1, min(3, (int)edges.size()));
            for (int i = 0; i < dupCnt && (int)edges.size() < Mlimit; ++i) {
                Edge base = rnd.any(edges);
                int nc = rnd.next(0, 25);
                edges.push_back({base.a, base.b, nc});
            }
            break;
        }
    }

    // Global cap on number of edges for readability
    if ((int)edges.size() > Mlimit) {
        shuffle(edges.begin(), edges.end());
        edges.resize(Mlimit);
    }

    int M = (int)edges.size();

    println(N, M);
    println(P);
    for (const auto &e : edges) {
        cout << e.a << ' ' << e.b << ' ' << e.c << '\n';
    }

    return 0;
}
