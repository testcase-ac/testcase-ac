#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with a bias toward small/medium sizes
    int sizeType = rnd.next(0, 3);
    int N;
    if (sizeType == 0) {
        N = rnd.next(2, 3);      // very small
    } else if (sizeType == 1) {
        N = rnd.next(4, 6);      // small
    } else if (sizeType == 2) {
        N = rnd.next(7, 9);      // medium
    } else {
        N = rnd.next(10, 11);    // upper bound (still hand-checkable)
    }

    // Choose a tree shape
    int treeType = rnd.next(0, 3);

    vector<pair<int,int>> edges;
    edges.reserve(N - 1);

    if (treeType == 0) {
        // Chain
        for (int i = 2; i <= N; ++i)
            edges.push_back({i - 1, i});
    } else if (treeType == 1) {
        // Star centered at 1
        for (int i = 2; i <= N; ++i)
            edges.push_back({1, i});
    } else if (treeType == 2) {
        // Binary-heap-like tree
        for (int i = 2; i <= N; ++i)
            edges.push_back({i / 2, i});
    } else {
        // Random tree
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.push_back({p, i});
        }
    }

    // Randomize edge order for variability
    shuffle(edges.begin(), edges.end());

    // Build adjacency list and adjacency matrix
    vector<vector<int>> g(N + 1);
    vector<vector<bool>> isAdj(N + 1, vector<bool>(N + 1, false));
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        g[u].push_back(v);
        g[v].push_back(u);
        isAdj[u][v] = isAdj[v][u] = true;
    }

    // Root the tree at 1, compute parent and depth iteratively
    vector<int> parent(N + 1, -1);
    vector<int> depth(N + 1, 0);
    vector<int> st;
    st.push_back(1);
    parent[1] = 0;
    depth[1] = 0;
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        for (int to : g[v]) {
            if (to == parent[v]) continue;
            parent[to] = v;
            depth[to] = depth[v] + 1;
            st.push_back(to);
        }
    }

    // Helper: get path between u and v as a vector of vertices
    auto getPath = [&](int u, int v) {
        vector<int> pathU, pathV;
        int uu = u, vv = v;
        while (depth[uu] > depth[vv]) {
            pathU.push_back(uu);
            uu = parent[uu];
        }
        while (depth[vv] > depth[uu]) {
            pathV.push_back(vv);
            vv = parent[vv];
        }
        while (uu != vv) {
            pathU.push_back(uu);
            pathV.push_back(vv);
            uu = parent[uu];
            vv = parent[vv];
        }
        // uu == vv is LCA
        pathU.push_back(uu);
        // pathU: u -> ... -> LCA
        // pathV: v -> ... -> child of LCA (going upward), need to reverse
        reverse(pathV.begin(), pathV.end());
        vector<int> res = pathU;
        for (int x : pathV) res.push_back(x);
        return res;
    };

    // Decide number of queries, keeping total output compact
    int Q = rnd.next(5, 10);

    vector<vector<int>> qs;

    // 1) Single-vertex query
    {
        int v = rnd.next(1, N);
        qs.push_back(vector<int>{v});
    }

    // 2) All-vertices query
    {
        vector<int> s;
        for (int i = 1; i <= N; ++i) s.push_back(i);
        qs.push_back(s);
    }

    // 3) Adjacent pair query (if possible)
    if (N >= 2) {
        auto e = rnd.any(edges);
        vector<int> s = {e.first, e.second};
        if (rnd.next(0, 1)) swap(s[0], s[1]);
        qs.push_back(s);
    }

    // 4) Non-adjacent pair query (only meaningful if N >= 3)
    if (N >= 3) {
        int u, v;
        while (true) {
            u = rnd.next(1, N);
            v = rnd.next(1, N);
            if (u == v) continue;
            if (isAdj[u][v]) continue;
            break;
        }
        qs.push_back(vector<int>{u, v});
    }

    // 5) K = 3 query with nodes on (preferably) a path
    if (N >= 3) {
        vector<int> s;
        for (int attempt = 0; attempt < 5; ++attempt) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) continue;
            vector<int> path = getPath(u, v);
            if ((int)path.size() >= 3) {
                int a = path.front();
                int c = path.back();
                int b = path[(int)path.size() / 2];
                s = {a, b, c};
                break;
            }
        }
        if (s.empty()) {
            // Fallback: random 3 distinct nodes
            vector<int> nodes;
            for (int i = 1; i <= N; ++i) nodes.push_back(i);
            shuffle(nodes.begin(), nodes.end());
            s.assign(nodes.begin(), nodes.begin() + 3);
        }
        shuffle(s.begin(), s.end());
        qs.push_back(s);
    }

    // 6) Random subset query (2 <= K <= N-1 if N >= 3)
    if (N >= 2) {
        vector<int> s;
        if (N == 2) {
            s = {1, 2};
            shuffle(s.begin(), s.end());
        } else {
            int K = rnd.next(2, N - 1);
            vector<int> nodes;
            for (int i = 1; i <= N; ++i) nodes.push_back(i);
            shuffle(nodes.begin(), nodes.end());
            nodes.resize(K);
            s = nodes;
        }
        qs.push_back(s);
    }

    // 7) Path subset query
    if (N >= 2) {
        vector<int> s;
        for (int attempt = 0; attempt < 10; ++attempt) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) continue;
            vector<int> path = getPath(u, v);
            if ((int)path.size() >= 2) {
                s = path;
                break;
            }
        }
        if (s.empty()) {
            for (int i = 1; i <= min(2, N); ++i) s.push_back(i);
        }
        qs.push_back(s);
    }

    // Now adjust to exactly Q queries: trim or add random ones
    if ((int)qs.size() > Q) {
        shuffle(qs.begin(), qs.end());
        qs.resize(Q);
    } else {
        while ((int)qs.size() < Q) {
            vector<int> s;
            int t = rnd.next(0, 3);
            if (t == 0) {
                // Single or pair
                if (N == 1 || rnd.next(0, 1) == 0) {
                    int v = rnd.next(1, N);
                    s = {v};
                } else {
                    int u = rnd.next(1, N);
                    int v = rnd.next(1, N);
                    while (v == u) v = rnd.next(1, N);
                    s = {u, v};
                }
            } else if (t == 1) {
                // Random subset
                if (N == 1) {
                    s = {1};
                } else {
                    int K = rnd.next(1, N);
                    vector<int> nodes;
                    for (int i = 1; i <= N; ++i) nodes.push_back(i);
                    shuffle(nodes.begin(), nodes.end());
                    nodes.resize(K);
                    s = nodes;
                }
            } else if (t == 2) {
                // Path subset
                if (N >= 2) {
                    int u = rnd.next(1, N);
                    int v = rnd.next(1, N);
                    while (v == u) v = rnd.next(1, N);
                    s = getPath(u, v);
                } else {
                    s = {1};
                }
            } else {
                // Another all-nodes query
                for (int i = 1; i <= N; ++i) s.push_back(i);
            }
            qs.push_back(s);
        }
    }

    // Shuffle node order inside each query to avoid relying on sorted input
    for (auto &S : qs) {
        shuffle(S.begin(), S.end());
    }

    // Output
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(Q);
    for (auto &S : qs) {
        vector<int> row;
        row.reserve(S.size() + 1);
        row.push_back((int)S.size());
        for (int v : S) row.push_back(v);
        println(row);
    }

    return 0;
}
