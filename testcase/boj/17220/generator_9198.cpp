#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 7);
    int N = 0;
    vector<vector<bool>> adj;

    // Build graph depending on scenario
    switch (scenario) {
        case 1: { // Simple chain
            N = rnd.next(2, 10);
            adj.assign(N, vector<bool>(N, false));
            for (int i = 0; i < N - 1; ++i)
                adj[i][i + 1] = true;
            break;
        }
        case 2: { // Star from a single root
            N = rnd.next(3, 10);
            adj.assign(N, vector<bool>(N, false));
            for (int i = 1; i < N; ++i)
                adj[0][i] = true;
            // Sometimes add extra DAG edges among leaves
            if (rnd.next(0, 1) == 1) {
                for (int i = 1; i < N; ++i) {
                    for (int j = i + 1; j < N; ++j) {
                        if (rnd.next(0, 99) < 30) adj[i][j] = true;
                    }
                }
            }
            break;
        }
        case 3: { // Two disjoint chains
            N = rnd.next(6, 12);
            adj.assign(N, vector<bool>(N, false));
            int split = rnd.next(2, N - 2);
            for (int i = 0; i < split - 1; ++i)
                adj[i][i + 1] = true;
            for (int i = split; i < N - 1; ++i)
                adj[i][i + 1] = true;
            break;
        }
        case 4: { // Cycle with tails (may need fixing later for origin)
            N = rnd.next(3, 10);
            adj.assign(N, vector<bool>(N, false));
            int k = rnd.next(3, N); // cycle size
            for (int i = 0; i < k; ++i)
                adj[i][(i + 1) % k] = true;
            for (int v = k; v < N; ++v) {
                int u = rnd.next(0, k - 1);
                adj[u][v] = true;
            }
            break;
        }
        case 5: { // Layered DAG
            N = rnd.next(5, 12);
            adj.assign(N, vector<bool>(N, false));
            int L = rnd.next(2, min(4, N));
            vector<int> cnt(L, 1);
            int remaining = N - L;
            while (remaining--) {
                cnt[rnd.next(0, L - 1)]++;
            }
            vector<vector<int>> layerNodes(L);
            int cur = 0;
            for (int l = 0; l < L; ++l) {
                for (int t = 0; t < cnt[l]; ++t) {
                    layerNodes[l].push_back(cur++);
                }
            }
            int prob = rnd.next(30, 70); // edge density in percent
            for (int l = 0; l < L; ++l) {
                for (int h = l + 1; h < L; ++h) {
                    for (int u : layerNodes[l]) {
                        for (int v : layerNodes[h]) {
                            if (rnd.next(0, 99) < prob)
                                adj[u][v] = true;
                        }
                    }
                }
            }
            break;
        }
        case 6: { // Many origins
            N = rnd.next(5, 12);
            adj.assign(N, vector<bool>(N, false));
            int Korig = rnd.next(2, min(4, N - 1));
            // Origins: 0..Korig-1
            for (int o = 0; o < Korig; ++o) {
                int numOut = rnd.next(1, min(3, N - Korig));
                for (int e = 0; e < numOut; ++e) {
                    int v = rnd.next(Korig, N - 1);
                    if (o != v) adj[o][v] = true;
                }
            }
            // Edges among non-origin nodes, no edges into origins
            for (int i = Korig; i < N; ++i) {
                for (int j = Korig; j < N; ++j) {
                    if (i == j) continue;
                    if (!adj[i][j] && rnd.next(0, 99) < 30)
                        adj[i][j] = true;
                }
            }
            break;
        }
        case 7: { // Dense random directed graph (may need fixing for origin)
            N = rnd.next(4, 9);
            adj.assign(N, vector<bool>(N, false));
            int percent = rnd.next(40, 80);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i == j) continue;
                    if (rnd.next(0, 99) < percent)
                        adj[i][j] = true;
                }
            }
            break;
        }
    }

    // Ensure at least one edge, avoid self-loop
    bool hasEdge = false;
    for (int i = 0; i < N && !hasEdge; ++i)
        for (int j = 0; j < N && !hasEdge; ++j)
            if (adj[i][j]) hasEdge = true;

    if (!hasEdge && N >= 2) {
        adj[0][1] = true;
    }

    // Compute indegree and outdegree
    auto recomputeDegrees = [&](vector<int> &indeg, vector<int> &outdeg) {
        indeg.assign(N, 0);
        outdeg.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (adj[i][j]) {
                    outdeg[i]++;
                    indeg[j]++;
                }
            }
        }
    };

    vector<int> indeg, outdeg;
    recomputeDegrees(indeg, outdeg);

    // Ensure at least one origin: indegree 0 and outdegree >= 1
    vector<int> origins;
    for (int i = 0; i < N; ++i)
        if (indeg[i] == 0 && outdeg[i] > 0)
            origins.push_back(i);

    if (origins.empty()) {
        int o = rnd.next(0, N - 1); // choose a node to force as origin
        // Remove all incoming edges to o
        for (int u = 0; u < N; ++u) {
            if (u == o) continue;
            adj[u][o] = false;
        }
        // Ensure at least one outgoing edge from o
        bool hasOut = false;
        for (int v = 0; v < N; ++v) {
            if (adj[o][v]) {
                hasOut = true;
                break;
            }
        }
        if (!hasOut) {
            int v = (o + 1) % N;
            adj[o][v] = true;
        }
        // Recompute degrees after fix
        recomputeDegrees(indeg, outdeg);
    }

    // Recollect origins and leaves for capture strategy
    origins.clear();
    vector<int> leaves;
    for (int i = 0; i < N; ++i) {
        if (indeg[i] == 0 && outdeg[i] > 0)
            origins.push_back(i);
        if (outdeg[i] == 0 && indeg[i] > 0)
            leaves.push_back(i);
    }

    // Just in case, ensure at least one edge still exists
    hasEdge = false;
    for (int i = 0; i < N && !hasEdge; ++i)
        for (int j = 0; j < N && !hasEdge; ++j)
            if (adj[i][j]) hasEdge = true;
    if (!hasEdge && N >= 2) {
        int o = rnd.next(0, N - 1);
        int v = (o + 1) % N;
        adj[o][v] = true;
        recomputeDegrees(indeg, outdeg);
        origins.clear();
        leaves.clear();
        for (int i = 0; i < N; ++i) {
            if (indeg[i] == 0 && outdeg[i] > 0)
                origins.push_back(i);
            if (outdeg[i] == 0 && indeg[i] > 0)
                leaves.push_back(i);
        }
    }

    // Decide captured nodes
    vector<int> isCapt(N, 0);
    int captureType = rnd.next(0, 4);

    if (captureType == 0) {
        // Initially allow possibly none; we'll fix to have at least one later
        // Do nothing here
    } else if (captureType == 1) {
        // Random subset, at least one and not all (before final fix)
        int prob = rnd.next(20, 60);
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            if (rnd.next(0, 99) < prob) {
                isCapt[i] = 1;
                cnt++;
            }
        }
        if (cnt == 0) {
            int x = rnd.next(0, N - 1);
            isCapt[x] = 1;
            cnt = 1;
        }
        if (cnt == N) {
            int x = rnd.next(0, N - 1);
            isCapt[x] = 0;
        }
    } else if (captureType == 2) {
        // Capture origins mainly
        if (!origins.empty()) {
            int cnt = 0;
            for (int o : origins) {
                if ((int)origins.size() == 1 || rnd.next(0, 1) == 0) {
                    isCapt[o] = 1;
                    cnt++;
                }
            }
            if (cnt == 0) {
                int o = origins[rnd.next(0, (int)origins.size() - 1)];
                isCapt[o] = 1;
            }
            // Sometimes capture a few extra random nodes
            if (rnd.next(0, 1) == 1) {
                for (int i = 0; i < N; ++i) {
                    if (!isCapt[i] && rnd.next(0, 99) < 20)
                        isCapt[i] = 1;
                }
            }
        } else {
            // No origins: fallback to random subset
            int prob = rnd.next(20, 60);
            int cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 99) < prob) {
                    isCapt[i] = 1;
                    cnt++;
                }
            }
            if (cnt == 0) {
                int x = rnd.next(0, N - 1);
                isCapt[x] = 1;
            }
        }
    } else if (captureType == 3) {
        // Capture leaves mainly
        if (!leaves.empty()) {
            int cnt = 0;
            for (int v : leaves) {
                if ((int)leaves.size() == 1 || rnd.next(0, 1) == 0) {
                    isCapt[v] = 1;
                    cnt++;
                }
            }
            if (cnt == 0) {
                int v = leaves[rnd.next(0, (int)leaves.size() - 1)];
                isCapt[v] = 1;
            }
            // Sometimes capture extra random nodes
            if (rnd.next(0, 1) == 1) {
                for (int i = 0; i < N; ++i) {
                    if (!isCapt[i] && rnd.next(0, 99) < 20)
                        isCapt[i] = 1;
                }
            }
        } else {
            // No leaves: fallback to random subset
            int prob = rnd.next(20, 60);
            int cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 99) < prob) {
                    isCapt[i] = 1;
                    cnt++;
                }
            }
            if (cnt == 0) {
                int x = rnd.next(0, N - 1);
                isCapt[x] = 1;
            }
        }
    } else if (captureType == 4) {
        // Capture almost everyone
        int survivor = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i)
            if (i != survivor) isCapt[i] = 1;
    }

    // Ensure at least one captured node overall
    int K = 0;
    for (int i = 0; i < N; ++i)
        if (isCapt[i]) K++;
    if (K == 0) {
        int x = rnd.next(0, N - 1);
        isCapt[x] = 1;
        K = 1;
    }

    // Build edges list
    vector<pair<int,int>> edges;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (adj[i][j])
                edges.push_back({i, j});

    int M = (int)edges.size();

    // Output graph
    println(N, M);
    for (auto &e : edges) {
        char a = char('A' + e.first);
        char b = char('A' + e.second);
        println(a, b);
    }

    // Output captured nodes
    vector<char> capturedLabels;
    for (int i = 0; i < N; ++i)
        if (isCapt[i])
            capturedLabels.push_back(char('A' + i));

    K = (int)capturedLabels.size();
    // K >= 1 by construction
    printf("%d", K);
    for (char c : capturedLabels)
        printf(" %c", c);
    printf("\n");

    return 0;
}
