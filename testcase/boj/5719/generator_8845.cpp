#include "testlib.h"
using namespace std;

struct Edge {
    int u, v, w;
};

struct Test {
    int N, S, D;
    vector<Edge> edges;
};

void addEdgeUnique(int u, int v, int w, vector<vector<bool>>& used, vector<Edge>& edges) {
    int N = (int)used.size();
    if (u == v) return;
    if (u < 0 || v < 0 || u >= N || v >= N) return;
    if (used[u][v]) return;
    used[u][v] = true;
    edges.push_back({u, v, w});
}

void finalizeTest(Test &t) {
    int N = t.N;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) p[i] = i;
    shuffle(p.begin(), p.end());

    for (auto &e : t.edges) {
        e.u = p[e.u];
        e.v = p[e.v];
    }
    t.S = p[t.S];
    t.D = p[t.D];

    shuffle(t.edges.begin(), t.edges.end());
}

Test buildCase1() {
    // Unique shortest path, but an almost shortest path exists
    Test t;
    int Lp = rnd.next(2, 3);          // length of main shortest path in edges
    int pathNodes = Lp + 1;
    int extra = rnd.next(1, 2);       // extra nodes used for alternative paths
    t.N = pathNodes + extra;
    t.S = 0;
    t.D = Lp;

    vector<vector<bool>> used(t.N, vector<bool>(t.N, false));

    // Main shortest path: 0 -> 1 -> ... -> Lp
    for (int i = 0; i < Lp; ++i) {
        addEdgeUnique(i, i + 1, 1, used, t.edges);
    }

    int firstExtra = pathNodes;

    // Alternative path using only heavy edges (not on any shortest path)
    if (extra == 1 || rnd.next(0, 1) == 0) {
        int x = firstExtra;
        addEdgeUnique(0, x, rnd.next(4, 8), used, t.edges);
        addEdgeUnique(x, t.D, rnd.next(4, 8), used, t.edges);
    } else {
        int x = firstExtra;
        int y = firstExtra + 1;
        addEdgeUnique(0, x, rnd.next(4, 8), used, t.edges);
        addEdgeUnique(x, y, rnd.next(4, 8), used, t.edges);
        addEdgeUnique(y, t.D, rnd.next(4, 8), used, t.edges);
    }

    // Some extra heavy edges that cannot form shortest paths
    int noiseCnt = rnd.next(0, 2);
    for (int k = 0; k < noiseCnt; ++k) {
        for (int it = 0; it < 20; ++it) {
            int u = rnd.next(0, t.N - 1);
            int v = rnd.next(0, t.N - 1);
            if (u == v) continue;
            if (used[u][v]) continue;
            addEdgeUnique(u, v, rnd.next(4, 8), used, t.edges);
            break;
        }
    }

    finalizeTest(t);
    return t;
}

Test buildCase2() {
    // Multiple distinct shortest paths exist, and an almost shortest path too
    Test t;
    t.N = rnd.next(5, 7);
    t.S = 0;
    t.D = 4; // needs at least 5 nodes, ensured by N in [5,7]

    vector<vector<bool>> used(t.N, vector<bool>(t.N, false));

    // Two shortest paths of length 2:
    // 0 -> 1 -> 4 and 0 -> 2 -> 4
    addEdgeUnique(0, 1, 1, used, t.edges);
    addEdgeUnique(1, 4, 1, used, t.edges);
    addEdgeUnique(0, 2, 1, used, t.edges);
    addEdgeUnique(2, 4, 1, used, t.edges);

    // Longer alternative path via node 3
    addEdgeUnique(0, 3, rnd.next(3, 5), used, t.edges);
    addEdgeUnique(3, 4, rnd.next(3, 5), used, t.edges);

    // Extra heavy edges; can't create new shortest paths (weights >= 3)
    int noiseCnt = rnd.next(0, 2);
    for (int k = 0; k < noiseCnt; ++k) {
        for (int it = 0; it < 20; ++it) {
            int u = rnd.next(0, t.N - 1);
            int v = rnd.next(0, t.N - 1);
            if (u == v) continue;
            if (used[u][v]) continue;
            addEdgeUnique(u, v, rnd.next(3, 8), used, t.edges);
            break;
        }
    }

    finalizeTest(t);
    return t;
}

Test buildCase3() {
    // There is a unique shortest path, and after removing its edges, no path remains
    Test t;
    t.N = rnd.next(4, 6);
    t.S = 0;
    t.D = 3; // will use nodes 0..3 for main path

    vector<vector<bool>> used(t.N, vector<bool>(t.N, false));

    // Main shortest path: 0 -> 1 -> 2 -> 3
    addEdgeUnique(0, 1, 1, used, t.edges);
    addEdgeUnique(1, 2, 1, used, t.edges);
    addEdgeUnique(2, 3, 1, used, t.edges);

    // Noise edges that cannot form an S->D path without using a shortest-path edge:
    // - no edge leaves S (0) except 0->1 already added
    // - no edge enters D (3) except 2->3 already added
    int noiseCnt = rnd.next(0, 3);
    for (int k = 0; k < noiseCnt; ++k) {
        for (int it = 0; it < 30; ++it) {
            int u = rnd.next(1, t.N - 1);          // never 0 as source
            int v = rnd.next(0, t.N - 1);
            if (v == 3) continue;                  // never into D
            if (u == v) continue;
            if (used[u][v]) continue;
            addEdgeUnique(u, v, rnd.next(3, 8), used, t.edges);
            break;
        }
    }

    finalizeTest(t);
    return t;
}

Test buildCase4() {
    // No path from S to D at all
    Test t;
    t.N = rnd.next(2, 6);
    t.S = 0;
    t.D = t.N - 1;

    vector<vector<bool>> used(t.N, vector<bool>(t.N, false));

    // Ensure S has no outgoing edges: all edges have source != S
    int maxEdges = (t.N - 1) * t.N - (t.N - 1); // u in [1..N-1], v in [0..N-1], u!=v
    int target = rnd.next(1, min(4, maxEdges));

    while ((int)t.edges.size() < target) {
        int u = rnd.next(1, t.N - 1);     // never S
        int v = rnd.next(0, t.N - 1);
        if (u == v) continue;
        if (used[u][v]) continue;
        addEdgeUnique(u, v, rnd.next(1, 9), used, t.edges);
    }

    finalizeTest(t);
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Test> tests;
    tests.push_back(buildCase1());
    tests.push_back(buildCase2());
    tests.push_back(buildCase3());
    tests.push_back(buildCase4());

    // Shuffle order of testcases
    shuffle(tests.begin(), tests.end());

    for (const auto &t : tests) {
        println(t.N, (int)t.edges.size());
        println(t.S, t.D);
        for (const auto &e : t.edges) {
            println(e.u, e.v, e.w);
        }
    }

    // Terminating line
    println(0, 0);

    return 0;
}
