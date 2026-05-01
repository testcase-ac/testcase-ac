#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct DSU {
    int n;
    vector<int> par, sz, mn;
    DSU(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        par.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        mn.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            par[i] = i;
            mn[i] = i;
        }
    }
    int find(int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        mn[a] = min(mn[a], mn[b]);
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    int getMin(int x) {
        return mn[find(x)];
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some variability but keep small
    int caseType = rnd.next(0, 2); // 0,1,2
    int N;
    if (caseType == 0) N = rnd.next(2, 5);
    else if (caseType == 1) N = rnd.next(6, 10);
    else N = rnd.next(11, 15);

    // Choose Q small/medium, but enough for some structure
    int Qmin = max(2, N - 1);
    int Qmax = max(Qmin, min(30, 2 * N + 5));
    int Q = rnd.next(Qmin, Qmax);

    // Decide number of type-1 (edge) queries
    int maxEdges = min(N - 1, Q - 1); // keep at least one type-2
    int E;
    if (maxEdges <= 0) {
        E = 0;
    } else {
        int minEdges = 1;
        E = rnd.next(minEdges, maxEdges);
        // Sometimes force to maximum edges for a full tree
        if (rnd.next(0, 4) == 0) E = maxEdges;
    }

    // Prepare query types: 1 for edge, 2 for ask
    vector<int> types(Q, 2);
    for (int i = 0; i < E; ++i) types[i] = 1;
    shuffle(types.begin(), types.end());

    DSU dsuGen(N);
    vector<vector<int>> gGen(N + 1);
    vector<tuple<int,int,int>> queries; // (T, A, B)

    // Helper to rebuild components for generation
    auto buildComponents = [&](vector<vector<int>>& comps, vector<int>& roots) {
        comps.assign(N + 1, vector<int>());
        for (int v = 1; v <= N; ++v) {
            comps[dsuGen.find(v)].push_back(v);
        }
        roots.clear();
        for (int r = 1; r <= N; ++r) {
            if (!comps[r].empty()) roots.push_back(r);
        }
    };

    // Generate high-level queries (T, A, B) without XOR
    for (int i = 0; i < Q; ++i) {
        int T = types[i];
        if (T == 1) {
            // Add an edge between two different components
            vector<vector<int>> comps;
            vector<int> roots;
            buildComponents(comps, roots);

            // There should always be at least 2 components here
            int idx1 = rnd.next(0, (int)roots.size() - 1);
            int idx2 = rnd.next(0, (int)roots.size() - 2);
            if (idx2 >= idx1) ++idx2;

            int r1 = roots[idx1];
            int r2 = roots[idx2];

            int A = rnd.any(comps[r1]);
            int B = rnd.any(comps[r2]);

            queries.emplace_back(1, A, B);
            dsuGen.unite(A, B);
            gGen[A].push_back(B);
            gGen[B].push_back(A);
        } else {
            // Type-2 query: choose A, B with some strategy
            vector<vector<int>> comps(N + 1);
            vector<int> roots;
            for (int v = 1; v <= N; ++v) {
                comps[dsuGen.find(v)].push_back(v);
            }
            for (int r = 1; r <= N; ++r) if (!comps[r].empty()) roots.push_back(r);

            int A = 1, B = 1;
            int casePick = rnd.next(0, 9);
            bool done = false;

            // Prefer connected distinct pair
            if (casePick < 3) {
                vector<int> bigRoots;
                for (int r : roots) if (comps[r].size() >= 2) bigRoots.push_back(r);
                if (!bigRoots.empty()) {
                    int rt = rnd.any(bigRoots);
                    A = rnd.any(comps[rt]);
                    do { B = rnd.any(comps[rt]); } while (B == A);
                    done = true;
                }
            }

            // Prefer disconnected pair
            if (!done && casePick >= 3 && casePick < 6) {
                if (roots.size() >= 2) {
                    int idx1 = rnd.next(0, (int)roots.size() - 1);
                    int idx2 = rnd.next(0, (int)roots.size() - 2);
                    if (idx2 >= idx1) ++idx2;
                    int r1 = roots[idx1], r2 = roots[idx2];
                    A = rnd.any(comps[r1]);
                    B = rnd.any(comps[r2]);
                    done = true;
                }
            }

            // A == B
            if (!done && casePick >= 6 && casePick < 8) {
                A = rnd.next(1, N);
                B = A;
                done = true;
            }

            // Fully random
            if (!done) {
                A = rnd.next(1, N);
                B = rnd.next(1, N);
            }

            queries.emplace_back(2, A, B);
        }
    }

    // Now output with XOR obfuscation, computing last_ans online
    println(N, Q);

    DSU dsuOut(N);
    vector<vector<int>> gOut(N + 1);
    int last_ans = 0;

    const int INF = 1000000007;

    for (int i = 0; i < Q; ++i) {
        int T, A, B;
        tie(T, A, B) = queries[i];

        int X = A ^ last_ans;
        int Y = B ^ last_ans;

        println(T, X, Y);

        if (T == 1) {
            // Apply edge in actual graph
            dsuOut.unite(A, B);
            gOut[A].push_back(B);
            gOut[B].push_back(A);
        } else {
            int ans = 0;
            if (!dsuOut.same(A, B)) {
                ans = 0;
            } else {
                int manager = dsuOut.getMin(A);

                // BFS from manager to get distances
                vector<int> dist(N + 1, INF);
                queue<int> q;
                dist[manager] = 0;
                q.push(manager);
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : gOut[u]) {
                        if (dist[v] == INF) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }

                // BFS from A to reconstruct path to B
                vector<int> par(N + 1, -1);
                vector<char> vis(N + 1, 0);
                queue<int> q2;
                q2.push(A);
                vis[A] = 1;
                par[A] = 0;
                while (!q2.empty()) {
                    int u = q2.front(); q2.pop();
                    if (u == B) break;
                    for (int v : gOut[u]) {
                        if (!vis[v]) {
                            vis[v] = 1;
                            par[v] = u;
                            q2.push(v);
                        }
                    }
                }

                vector<int> path;
                int cur = B;
                path.push_back(cur);
                while (cur != A) {
                    cur = par[cur];
                    path.push_back(cur);
                }
                reverse(path.begin(), path.end());

                ans = path[0];
                int bestDist = dist[ans];
                for (int v : path) {
                    if (dist[v] < bestDist) {
                        bestDist = dist[v];
                        ans = v;
                    } else if (dist[v] == bestDist && v < ans) {
                        // Tie-break by smaller index for determinism
                        ans = v;
                    }
                }
            }
            last_ans = ans;
        }
    }

    return 0;
}
