#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5); // 6 different patterns: 0..5

    int N = 0;
    vector<int> vis;
    vector<Edge> edges;

    if (mode == 0) {
        // Mode 0: Simple line, all intermediates safe
        N = rnd.next(2, 8);
        vis.assign(N, 0);
        vis[N - 1] = 1; // nexus visible

        for (int i = 0; i < N - 1; ++i) {
            int u = i, v = i + 1;
            int w;
            if (rnd.next(0, 9) == 0) w = rnd.next(50000, 100000);
            else w = rnd.next(1, 20);
            // optionally flip orientation (graph is undirected anyway)
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }
    } else if (mode == 1) {
        // Mode 1: Line + extra random edges, all intermediates safe
        N = rnd.next(3, 10);
        vis.assign(N, 0);
        vis[N - 1] = 1;

        vector<vector<char>> used(N, vector<char>(N, 0));

        // Base line to ensure connectivity
        for (int i = 0; i < N - 1; ++i) {
            int u = i, v = i + 1;
            int w = rnd.next(1, 20);
            used[u][v] = used[v][u] = 1;
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }

        // Add some extra edges without rejection
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (!used[i][j])
                    cand.push_back({i, j});
        shuffle(cand.begin(), cand.end());

        int totalPairs = N * (N - 1) / 2;
        int maxTotalEdges = min(20, totalPairs);
        int baseEdges = (int)edges.size();
        int maxExtra = maxTotalEdges - baseEdges;
        if (maxExtra < 0) maxExtra = 0;
        if (maxExtra > (int)cand.size()) maxExtra = (int)cand.size();
        int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);

        for (int i = 0; i < extra; ++i) {
            int u = cand[i].first;
            int v = cand[i].second;
            int w = rnd.next(1, 20);
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }
    } else if (mode == 2) {
        // Mode 2: Some blocked nodes, but ensure one safe path exists
        N = rnd.next(5, 10);
        vis.assign(N, 0);
        vis[0] = 0;
        vis[N - 1] = 1;

        // Random visibility for intermediates
        for (int i = 1; i <= N - 2; ++i)
            vis[i] = rnd.next(0, 1);

        vector<vector<char>> used(N, vector<char>(N, 0));

        // Force a safe path 0 -> ... -> N-1 through safe intermediates
        int maxL = min(4, N - 2);
        int L = rnd.next(1, maxL); // number of internal nodes on forced path

        vector<int> mids;
        for (int i = 1; i <= N - 2; ++i) mids.push_back(i);
        shuffle(mids.begin(), mids.end());

        vector<int> path;
        path.push_back(0);
        for (int i = 0; i < L; ++i) {
            int node = mids[i];
            path.push_back(node);
            vis[node] = 0; // ensure safe
        }
        path.push_back(N - 1); // nexus

        for (int i = 0; i + 1 < (int)path.size(); ++i) {
            int u = path[i];
            int v = path[i + 1];
            used[u][v] = used[v][u] = 1;
            int w = rnd.next(1, 20);
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }

        // Add some random extra edges (can go through visible nodes)
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (!used[i][j])
                    cand.push_back({i, j});
        shuffle(cand.begin(), cand.end());

        int totalPairs = N * (N - 1) / 2;
        int maxTotalEdges = min(20, totalPairs);
        int baseEdges = (int)edges.size();
        int maxExtra = maxTotalEdges - baseEdges;
        if (maxExtra < 0) maxExtra = 0;
        if (maxExtra > (int)cand.size()) maxExtra = (int)cand.size();
        int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);

        for (int i = 0; i < extra; ++i) {
            int u = cand[i].first;
            int v = cand[i].second;
            int w = rnd.next(1, 20);
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }
    } else if (mode == 3) {
        // Mode 3: No valid path (all intermediates visible)
        N = rnd.next(3, 9);
        vis.assign(N, 1);
        vis[0] = 0;
        vis[N - 1] = 1;

        vector<vector<char>> used(N, vector<char>(N, 0));

        // Star-like structure: 0 -- i -- (N-1)
        for (int i = 1; i <= N - 2; ++i) {
            int u = 0, v = i;
            int w1 = rnd.next(1, 20);
            used[u][v] = used[v][u] = 1;
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w1});

            u = i; v = N - 1;
            int w2 = rnd.next(1, 20);
            used[u][v] = used[v][u] = 1;
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w2});
        }

        // Extra edges but forbid direct 0-(N-1)
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j) {
                if (used[i][j]) continue;
                if (i == 0 && j == N - 1) continue;
                cand.push_back({i, j});
            }
        shuffle(cand.begin(), cand.end());

        int totalPairs = N * (N - 1) / 2 - 1; // minus (0,N-1)
        int maxTotalEdges = min(20, totalPairs);
        int baseEdges = (int)edges.size();
        int maxExtra = maxTotalEdges - baseEdges;
        if (maxExtra < 0) maxExtra = 0;
        if (maxExtra > (int)cand.size()) maxExtra = (int)cand.size();
        int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);

        for (int i = 0; i < extra; ++i) {
            int u = cand[i].first;
            int v = cand[i].second;
            int w = rnd.next(1, 20);
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }
    } else if (mode == 4) {
        // Mode 4: Tempting but invalid short path via visible node
        // N = 4, nodes: 0 (safe), 1 (visible), 2 (safe), 3 (nexus, visible)
        N = 4;
        vis.assign(N, 0);
        vis[0] = 0;
        vis[1] = 1;
        vis[2] = 0;
        vis[3] = 1;

        int w01 = 1, w13 = 1;
        int w02 = rnd.next(3, 8);
        int w23 = rnd.next(3, 8);

        edges.push_back({0, 1, w01});
        edges.push_back({1, 3, w13});
        edges.push_back({0, 2, w02});
        edges.push_back({2, 3, w23});
    } else {
        // Mode 5: Fully random small graph
        N = rnd.next(2, 10);
        vis.assign(N, 0);
        vis[0] = 0;
        vis[N - 1] = 1;
        for (int i = 1; i <= N - 2; ++i)
            vis[i] = rnd.next(0, 1);

        vector<pair<int,int>> allPairs;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                allPairs.push_back({i, j});
        shuffle(allPairs.begin(), allPairs.end());

        int totalPairs = (int)allPairs.size();
        int maxEdges = min(20, totalPairs);
        int E = rnd.next(1, maxEdges);

        for (int i = 0; i < E; ++i) {
            int u = allPairs[i].first;
            int v = allPairs[i].second;
            int w;
            if (rnd.next(0, 7) == 0) w = rnd.next(50000, 100000);
            else w = rnd.next(1, 20);
            if (rnd.next(0, 1)) swap(u, v);
            edges.push_back({u, v, w});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(edges.begin(), edges.end());
    }

    int M = (int)edges.size();
    if (M == 0) {
        // Ensure at least one edge; this situation should not normally occur,
        // but add a fallback simple edge if it does.
        if (N == 1) {
            // Degenerate; cannot have edges, but per problem M>=1; force N=2 case won't happen here.
        } else {
            int u = 0, v = N - 1;
            int w = 1;
            edges.push_back({u, v, w});
            M = 1;
        }
    }

    println(N, M);
    println(vis);
    for (const auto &e : edges) {
        println(e.u, e.v, e.w);
    }

    return 0;
}
