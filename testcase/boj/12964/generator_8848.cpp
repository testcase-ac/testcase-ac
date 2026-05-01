#include "testlib.h"
using namespace std;

vector<pair<int,int>> make_tree_star(int N, int center) {
    vector<pair<int,int>> edges;
    for (int v = 0; v < N; ++v) {
        if (v == center) continue;
        edges.push_back({center, v});
    }
    return edges;
}

vector<pair<int,int>> make_tree_path(int N) {
    vector<pair<int,int>> edges;
    for (int v = 1; v < N; ++v) {
        edges.push_back({v - 1, v});
    }
    return edges;
}

vector<pair<int,int>> make_tree_random(int N) {
    vector<pair<int,int>> edges;
    for (int v = 1; v < N; ++v) {
        int p = rnd.next(0, v - 1);
        edges.push_back({p, v});
    }
    return edges;
}

vector<pair<int,int>> make_tree_binary(int N) {
    vector<pair<int,int>> edges;
    for (int v = 1; v < N; ++v) {
        int p = (v - 1) / 2;
        edges.push_back({p, v});
    }
    return edges;
}

vector<vector<int>> build_adj(int N, const vector<pair<int,int>>& edges) {
    vector<vector<int>> g(N);
    for (auto e : edges) {
        int u = e.first, v = e.second;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with a bias towards small/medium sizes
    int modeN = rnd.next(0, 3);
    int N;
    if (modeN == 0) N = rnd.next(2, 4);
    else if (modeN == 1) N = rnd.next(5, 8);
    else N = rnd.next(9, 12);

    // Generate tree A
    int typeA = rnd.next(0, 3); // 0: star, 1: path, 2: random, 3: binary
    vector<pair<int,int>> edgesA;
    if (typeA == 0) {
        int center = rnd.next(0, N - 1);
        edgesA = make_tree_star(N, center);
    } else if (typeA == 1) {
        edgesA = make_tree_path(N);
    } else if (typeA == 2) {
        edgesA = make_tree_random(N);
    } else {
        edgesA = make_tree_binary(N);
    }

    // Possibly shuffle edges of A for variability
    if (rnd.next(0, 1)) {
        shuffle(edgesA.begin(), edgesA.end());
    }

    // Generate tree B using several structural modes
    vector<pair<int,int>> edgesB;
    int modeB = rnd.next(0, 4);
    if (modeB == 0) {
        // Exactly the same as A
        edgesB = edgesA;
    } else if (modeB == 1) {
        // Permute labels of A
        vector<int> perm(N);
        for (int i = 0; i < N; ++i) perm[i] = i;
        shuffle(perm.begin(), perm.end());
        for (auto e : edgesA) {
            int u = perm[e.first];
            int v = perm[e.second];
            edgesB.push_back({u, v});
        }
    } else if (modeB == 2) {
        // Independent random tree (mix of types)
        int typeB = rnd.next(0, 3);
        if (typeB == 0) {
            int center = rnd.next(0, N - 1);
            edgesB = make_tree_star(N, center);
        } else if (typeB == 1) {
            edgesB = make_tree_path(N);
        } else if (typeB == 2) {
            edgesB = make_tree_random(N);
        } else {
            edgesB = make_tree_binary(N);
        }
    } else if (modeB == 3) {
        // Force B to be a path
        edgesB = make_tree_path(N);
    } else {
        // Force B to be a star
        int center = rnd.next(0, N - 1);
        edgesB = make_tree_star(N, center);
    }

    if (rnd.next(0, 1)) {
        shuffle(edgesB.begin(), edgesB.end());
    }

    // Build adjacency for A for possible clustered score patterns
    vector<vector<int>> gA = build_adj(N, edgesA);

    // Generate scores
    vector<int> s(N, 0);
    int scoreMode = rnd.next(0, 5); // 0..5 different patterns
    if (scoreMode == 0) {
        // All positive, small
        for (int i = 0; i < N; ++i) {
            s[i] = rnd.next(1, 20);
        }
    } else if (scoreMode == 1) {
        // Mixed small negatives and positives
        for (int i = 0; i < N; ++i) {
            s[i] = rnd.next(-10, 10);
        }
    } else if (scoreMode == 2) {
        // Mostly negative, some positives
        bool hasPositive = false;
        for (int i = 0; i < N; ++i) {
            if (rnd.next(0, 4) == 0) {
                s[i] = rnd.next(1, 15);
                hasPositive = true;
            } else {
                s[i] = rnd.next(-10, -1);
            }
        }
        if (!hasPositive) {
            int idx = rnd.next(0, N - 1);
            s[idx] = rnd.next(1, 15);
        }
    } else if (scoreMode == 3) {
        // One big positive, others small (sometimes negative)
        int big = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == big) {
                s[i] = rnd.next(100, 300);
            } else {
                s[i] = rnd.next(-10, 5);
            }
        }
    } else if (scoreMode == 4) {
        // Cluster of positives connected in A, others mostly negative
        int root = rnd.next(0, N - 1);
        int L = rnd.next(2, min(N, 5));
        vector<int> visited(N, 0);
        vector<int> q(N);
        int ql = 0, qr = 0;
        q[qr++] = root;
        visited[root] = 1;
        vector<int> cluster;
        while (ql < qr && (int)cluster.size() < L) {
            int v = q[ql++];
            cluster.push_back(v);
            for (int to : gA[v]) {
                if (!visited[to]) {
                    visited[to] = 1;
                    q[qr++] = to;
                }
            }
        }
        vector<int> inCluster(N, 0);
        for (int v : cluster) inCluster[v] = 1;
        for (int i = 0; i < N; ++i) {
            if (inCluster[i]) {
                s[i] = rnd.next(5, 20);
            } else {
                s[i] = rnd.next(-10, 2);
            }
        }
    } else {
        // All negative
        for (int i = 0; i < N; ++i) {
            s[i] = rnd.next(-10, -1);
        }
    }

    // Output
    println(N);
    for (auto e : edgesA) {
        println(e.first, e.second);
    }
    for (auto e : edgesB) {
        println(e.first, e.second);
    }
    println(s);

    return 0;
}
