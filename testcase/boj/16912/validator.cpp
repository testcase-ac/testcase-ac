#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int type, a, b;
};

struct DSUOp {
    int u, v, prev_size_u;
};

int N, M;
vector<Query> queries;
vector<vector<pair<int,int>>> seg; // segment tree: list of edges (u,v)
vector<DSUOp> stk;
vector<int> parent_dsu, size_dsu;

int find_set(int x) {
    while (parent_dsu[x] != x) x = parent_dsu[x];
    return x;
}

void unite(int u, int v) {
    int ru = find_set(u);
    int rv = find_set(v);
    if (ru == rv) return;
    if (size_dsu[ru] < size_dsu[rv]) swap(ru, rv);
    // attach rv under ru
    stk.push_back({ru, rv, size_dsu[ru]});
    parent_dsu[rv] = ru;
    size_dsu[ru] += size_dsu[rv];
}

void rollback(int snapshot) {
    while ((int)stk.size() > snapshot) {
        DSUOp op = stk.back();
        stk.pop_back();
        parent_dsu[op.v] = op.v;
        size_dsu[op.u] = op.prev_size_u;
    }
}

// add edge (u,v) to segment tree on interval [ql, qr]
void addEdge(int node, int l, int r, int ql, int qr, pair<int,int> edge) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        seg[node].push_back(edge);
        return;
    }
    int mid = (l + r) >> 1;
    addEdge(node<<1,     l,   mid, ql, qr, edge);
    addEdge(node<<1|1, mid+1,     r, ql, qr, edge);
}

void dfs(int node, int l, int r) {
    int snap = stk.size();
    // apply all edges in this segment
    for (auto &e : seg[node]) {
        unite(e.first, e.second);
    }
    if (l == r) {
        // process query at time l
        const Query &q = queries[l];
        if (q.type == 1) {
            // adding edge at time l: must not create cycle
            int ra = find_set(q.a);
            int rb = find_set(q.b);
            ensuref(ra != rb,
                    "Cycle detected by adding edge (%d, %d) at query %d", 
                    q.a, q.b, l);
        }
    } else {
        int mid = (l + r) >> 1;
        dfs(node<<1,     l,   mid);
        dfs(node<<1|1, mid+1,     r);
    }
    rollback(snap);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    queries.resize(M+2);

    // Map from edge to stack of addition times
    map<pair<int,int>, vector<int>> add_stack;
    vector<tuple<int,int,int,int>> intervals; 
    intervals.reserve(M);

    for (int i = 1; i <= M; i++) {
        int t = inf.readInt(1, 3, "t_i");
        inf.readSpace();
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(a != b, "Query %d has A == B (%d)", i, a);

        queries[i] = {t, a, b};

        pair<int,int> edge = make_pair(min(a,b), max(a,b));
        if (t == 1) {
            // add edge
            add_stack[edge].push_back(i);
        } else if (t == 2) {
            // remove edge: must exist
            auto &stk_ev = add_stack[edge];
            ensuref(!stk_ev.empty(),
                    "Removing non-existent edge (%d, %d) at query %d", 
                    edge.first, edge.second, i);
            int add_time = stk_ev.back();
            stk_ev.pop_back();
            // record interval [add_time, i)
            intervals.emplace_back(edge.first, edge.second, add_time, i);
        } else {
            // query type 3: nothing to match now
        }
    }

    // Remaining active adds last until M+1
    for (auto &it : add_stack) {
        const pair<int,int> &edge = it.first;
        auto &stk_ev = it.second;
        for (int add_time : stk_ev) {
            intervals.emplace_back(edge.first, edge.second, add_time, M+1);
        }
    }

    // Build segment tree over times [1..M]
    seg.assign(4*(M+5), vector<pair<int,int>>());

    // For each interval [add_time, rem_time), active at times (add_time .. rem_time-1]
    for (auto &tp : intervals) {
        int u, v, lt, rt;
        tie(u, v, lt, rt) = tp;
        int l = lt + 1;
        int r = rt - 1;
        if (l <= r) {
            addEdge(1, 1, M, l, r, {u, v});
        }
    }

    // Initialize DSU
    parent_dsu.resize(N+1);
    size_dsu.resize(N+1);
    for (int i = 1; i <= N; i++) {
        parent_dsu[i] = i;
        size_dsu[i] = 1;
    }
    stk.clear();

    // Traverse segment tree and detect cycles on additions
    dfs(1, 1, M);

    inf.readEof();
    return 0;
}
