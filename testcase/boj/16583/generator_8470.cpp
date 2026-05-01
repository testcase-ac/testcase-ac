#include "testlib.h"
using namespace std;

void add_edge(int u, int v, vector<pair<int,int>>& edges, vector<vector<int>>& adj) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (adj[u][v]) return;
    adj[u][v] = adj[v][u] = 1;
    edges.push_back({u, v});
}

void gen_random_graph(int &N, vector<pair<int,int>> &edges) {
    N = rnd.next(2, 12);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));

    // Choose density type: sparse / medium / dense
    int dt = rnd.next(0, 2);
    double dens;
    if (dt == 0) dens = 0.2;
    else if (dt == 1) dens = 0.5;
    else dens = 0.8;

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (rnd.next() < dens) {
                add_edge(i, j, edges, adj);
            }
        }
    }

    // Ensure at least one edge to satisfy constraints
    if (edges.empty()) {
        add_edge(1, 2, edges, adj);
    }
}

void gen_star_graph(int &N, vector<pair<int,int>> &edges) {
    N = rnd.next(3, 12);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));
    int center = 1;

    // Degree of center at least 2 to allow boomerangs
    int deg = rnd.next(2, N - 1);
    vector<int> nodes;
    for (int i = 2; i <= N; ++i) nodes.push_back(i);
    shuffle(nodes.begin(), nodes.end());
    for (int i = 0; i < deg; ++i) {
        add_edge(center, nodes[i], edges, adj);
    }

    // Add some extra random edges to create variety
    int extra = rnd.next(0, N - 2);
    for (int k = 0; k < extra; ++k) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v) { --k; continue; }
        add_edge(u, v, edges, adj);
    }
}

void gen_clique_like(int &N, vector<pair<int,int>> &edges) {
    N = rnd.next(3, 8);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));

    // Very dense graph, close to a clique
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            // Probability biased to be dense
            if (rnd.next() < 0.75) {
                add_edge(i, j, edges, adj);
            }
        }
    }

    // Ensure at least one edge
    if (edges.empty()) {
        add_edge(1, 2, edges, adj);
    }
}

void gen_two_centers(int &N, vector<pair<int,int>> &edges) {
    N = rnd.next(4, 12);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));
    int a = 1, b = 2;

    // Every other vertex connects to both centers
    for (int i = 3; i <= N; ++i) {
        add_edge(a, i, edges, adj);
        add_edge(b, i, edges, adj);
    }

    // Optionally connect the centers directly
    if (rnd.next(0, 1)) {
        add_edge(a, b, edges, adj);
    }

    // Some random extra edges among leaves
    int extra = rnd.next(0, N - 3);
    for (int k = 0; k < extra; ++k) {
        int u = rnd.next(3, N);
        int v = rnd.next(3, N);
        if (u == v) { --k; continue; }
        add_edge(u, v, edges, adj);
    }
}

void gen_components(int &N, vector<pair<int,int>> &edges) {
    N = rnd.next(4, 12);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));

    int remaining = N;
    int start = 1;
    while (remaining > 0) {
        int maxSz = min(4, remaining);
        int sz = rnd.next(2, maxSz);
        if (remaining - sz == 1) sz++; // avoid isolated single vertex
        if (sz > remaining) sz = remaining;

        // Choose component type
        int type = rnd.next(0, 2);
        if (sz == 2) {
            // Simple edge
            add_edge(start, start + 1, edges, adj);
        } else if (sz == 3) {
            if (type == 0) {
                // Path of length 2
                add_edge(start, start + 1, edges, adj);
                add_edge(start + 1, start + 2, edges, adj);
            } else {
                // Triangle
                add_edge(start, start + 1, edges, adj);
                add_edge(start + 1, start + 2, edges, adj);
                add_edge(start, start + 2, edges, adj);
            }
        } else if (sz == 4) {
            if (type == 0) {
                // 4-cycle
                add_edge(start, start + 1, edges, adj);
                add_edge(start + 1, start + 2, edges, adj);
                add_edge(start + 2, start + 3, edges, adj);
                add_edge(start + 3, start, edges, adj);
            } else if (type == 1) {
                // Path on 4 vertices
                add_edge(start, start + 1, edges, adj);
                add_edge(start + 1, start + 2, edges, adj);
                add_edge(start + 2, start + 3, edges, adj);
            } else {
                // Triangle plus a leaf
                add_edge(start, start + 1, edges, adj);
                add_edge(start + 1, start + 2, edges, adj);
                add_edge(start, start + 2, edges, adj);
                add_edge(start + 2, start + 3, edges, adj);
            }
        }

        start += sz;
        remaining -= sz;
    }

    if (edges.empty()) {
        add_edge(1, min(2, N), edges, adj);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0;
    vector<pair<int,int>> edges;

    int pattern = rnd.next(0, 4); // 5 patterns: 0..4
    if (pattern == 0) {
        gen_random_graph(N, edges);
    } else if (pattern == 1) {
        gen_star_graph(N, edges);
    } else if (pattern == 2) {
        gen_clique_like(N, edges);
    } else if (pattern == 3) {
        gen_two_centers(N, edges);
    } else {
        gen_components(N, edges);
    }

    // Randomly permute vertex labels to avoid fixed structures
    vector<int> p0 = rnd.perm(N); // values 0..N-1
    vector<int> perm(N + 1);
    for (int i = 0; i < N; ++i) perm[i + 1] = p0[i] + 1;

    vector<pair<int,int>> mapped;
    mapped.reserve(edges.size());
    for (auto e : edges) {
        int u = perm[e.first];
        int v = perm[e.second];
        if (u > v) swap(u, v);
        mapped.push_back({u, v});
    }

    sort(mapped.begin(), mapped.end());
    mapped.erase(unique(mapped.begin(), mapped.end()), mapped.end());
    edges.swap(mapped);

    println(N, (int)edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
