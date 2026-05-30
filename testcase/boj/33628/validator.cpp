#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// DSU (Union-Find) with component minimum tracking and size
struct DSU {
    int n;
    vector<int> p, rnk, cmin, sz;

    DSU(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        p.resize(n + 1);
        rnk.assign(n + 1, 0);
        cmin.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            cmin[i] = i;
        }
    }

    int find(int x) {
        if (p[x] == x) return x;
        p[x] = find(p[x]);
        return p[x];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rnk[ra] < rnk[rb]) swap(ra, rb);
        p[rb] = ra;
        sz[ra] += sz[rb];
        cmin[ra] = min(cmin[ra], cmin[rb]);
        if (rnk[ra] == rnk[rb]) ++rnk[ra];
    }

    int getMin(int x) {
        return cmin[find(x)];
    }

    int getSize(int x) {
        return sz[find(x)];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_Q = 500000;
    const int MAX_ENCODED = 131071;

    int N = inf.readInt(2, MAX_N, "N");
    inf.readSpace();
    int Q = inf.readInt(2, MAX_Q, "Q");
    inf.readEoln();

    DSU dsu(N);
    long long last_ans = 0;

    // We'll maintain the graph and verify required global properties
    vector<vector<int>> adj(N + 1);
    long long edgeCount = 0;

    for (int qi = 0; qi < Q; ++qi) {
        int T = inf.readInt(1, 2, "T");
        inf.readSpace();
        int X = inf.readInt(0, MAX_ENCODED, "X");
        inf.readSpace();
        int Y = inf.readInt(0, MAX_ENCODED, "Y");
        inf.readEoln();

        long long A_ll = (long long)X ^ last_ans;
        long long B_ll = (long long)Y ^ last_ans;

        // A and B as 32-bit ints, but we must check bounds as per problem
        int A = (int)A_ll;
        int B = (int)B_ll;

        // A,B must be within [1, N]
        ensuref(1 <= A && A <= N, 
                "Decoded A (X xor last_ans) out of range at query %d: A=%d, must be in [1,%d]", 
                qi + 1, A, N);
        ensuref(1 <= B && B <= N, 
                "Decoded B (Y xor last_ans) out of range at query %d: B=%d, must be in [1,%d]", 
                qi + 1, B, N);

        if (T == 1) {
            // Type 1: connect A and B.
            // Guarantee: before adding, there is no vertex reachable from both A and B
            // -> A and B are in different connected components.
            ensuref(!dsu.same(A, B),
                    "Type-1 query at index %d connects already-connected buildings: A=%d, B=%d",
                    qi + 1, A, B);

            // Update DSU and adjacency for later checks
            dsu.unite(A, B);
            adj[A].push_back(B);
            adj[B].push_back(A);
            ++edgeCount;
        } else { // T == 2
            // Type 2: we only check decoding; last_ans depends on correct output,
            // which validator does not know. However, we must simulate a consistent
            // last_ans to keep further xor-decoding consistent.
            //
            // From the input perspective, there is no extra structural promise
            // on answers except that last_ans is the output of previous type-2 queries.
            // We cannot verify the solution's correctness here.
            //
            // We must, however, update last_ans to some integer in [0, N] because
            // future X,Y are given with xor to that value and then are guaranteed
            // to decode into [1,N]. If we pick something outside [0, (1<<31)-1]
            // we may break that guarantee artificially.
            //
            // To stay consistent with constraints, we will compute the *true*
            // answer and use it as last_ans; this additionally enforces any
            // promises like "answer always exists / bounded".
            //
            // When not connected, correct answer is 0.
            int ans = 0;

            if (dsu.same(A, B)) {
                // Graph is an undirected forest because edges only added between
                // nodes from different components (no cycles).
                // In a tree, shortest path between A and B is unique.
                //
                // We must find among nodes on this path the one minimizing
                // distance to manager(A) = minimum indexed vertex in A's component.
                int root = A;

                // We'll BFS from A to get parent and depth, then reconstruct path A-B
                // Then BFS from manager to get distance to manager along tree.
                // Component size is up to N, but Q and N are limited so this is OK
                // for validator.

                int compRoot = dsu.find(A);
                int manager = dsu.getMin(A);

                // Collect nodes of this component via BFS/DFS once: but easier is two BFS:
                // BFS from A within tree, but need component restriction. We'll just
                // allow traversal but only through visited; since graph is forest,
                // BFS will never leave component because there's no edge to outside
                // (we maintain global adjacency though; union-forest guarantee ensures
                // components are disjoint).
                int n = N;
                static vector<int> par, depth, distM;
                if ((int)par.size() != n + 1) {
                    par.assign(n + 1, -1);
                    depth.assign(n + 1, -1);
                    distM.assign(n + 1, -1);
                } else {
                    fill(par.begin(), par.end(), -1);
                    fill(depth.begin(), depth.end(), -1);
                    fill(distM.begin(), distM.end(), -1);
                }

                queue<int> q;
                depth[A] = 0;
                par[A] = -1;
                q.push(A);
                while (!q.empty()) {
                    int v = q.front(); q.pop();
                    for (int to : adj[v]) {
                        if (depth[to] == -1) {
                            depth[to] = depth[v] + 1;
                            par[to] = v;
                            q.push(to);
                        }
                    }
                }

                // If connected, depth[B] must be != -1
                ensuref(depth[B] != -1,
                        "Inconsistent DSU and graph at query %d: A=%d, B=%d marked connected but no path in edges",
                        qi + 1, A, B);

                // Reconstruct path from A to B
                vector<int> path;
                int cur = B;
                while (cur != -1) {
                    path.push_back(cur);
                    if (cur == A) break;
                    cur = par[cur];
                }
                reverse(path.begin(), path.end());
                ensuref(!path.empty() && path.front() == A && path.back() == B,
                        "Path reconstruction failed at query %d", qi + 1);

                // BFS from manager to get distances in tree
                queue<int> qm;
                distM[manager] = 0;
                qm.push(manager);
                while (!qm.empty()) {
                    int v = qm.front(); qm.pop();
                    for (int to : adj[v]) {
                        if (distM[to] == -1) {
                            distM[to] = distM[v] + 1;
                            qm.push(to);
                        }
                    }
                }

                // manager must reach A's component vertices
                for (int v : path) {
                    ensuref(distM[v] != -1,
                            "Manager BFS did not reach vertex on A-B path at query %d, vertex %d",
                            qi + 1, v);
                }

                // On path, choose vertex minimizing distance to manager
                int bestNode = path[0];
                int bestDist = distM[bestNode];
                for (int v : path) {
                    if (distM[v] < bestDist ||
                        (distM[v] == bestDist && v < bestNode)) {
                        bestDist = distM[v];
                        bestNode = v;
                    }
                }
                ans = bestNode;
            } else {
                ans = 0;
            }

            ensuref(0 <= ans && ans <= N,
                    "Computed answer out of expected range at query %d: ans=%d",
                    qi + 1, ans);

            last_ans = ans;
        }
    }

    // Additional global consistency checks:

    // 1) The graph must be a forest:
    //    edges = N - number_of_components_with_edges? Actually, DSU merges only
    //    when connecting different components, so cycles cannot form.
    //    No additional check needed beyond adjacency consistency we already used.
    //
    // 2) Optional: ensure undirected adjacency symmetric (already built symmetric).
    // We could do a small sanity check:
    for (int v = 1; v <= N; ++v) {
        for (int to : adj[v]) {
            // Edges added symmetrically; nothing more to check here.
            ensuref(1 <= to && to <= N,
                    "Adjacency contains out-of-range vertex: %d -> %d", v, to);
        }
    }

    inf.readEof();
    return 0;
}
