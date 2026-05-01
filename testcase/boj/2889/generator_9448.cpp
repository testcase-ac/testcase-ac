#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0;
    vector<pair<int,int>> edges;

    int maxType = 9;
    int type;
    if (argc > 2) {
        int t = atoi(argv[2]);
        if (t < 0) t = 0;
        if (t > maxType) t = maxType;
        type = t;
    } else {
        type = rnd.next(0, maxType);
    }

    if (type == 0) {
        // Very small graph, 1-2 edges
        N = rnd.next(2, 5);
        vector<pair<int,int>> allEdges;
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                allEdges.push_back({i, j});
        shuffle(allEdges.begin(), allEdges.end());
        int K = rnd.next(1, min(2, (int)allEdges.size()));
        edges.assign(allEdges.begin(), allEdges.begin() + K);
    } else if (type == 1) {
        // Path graph
        N = rnd.next(2, 10);
        for (int i = 1; i < N; ++i)
            edges.push_back({i, i + 1});
    } else if (type == 2) {
        // Star graph
        N = rnd.next(3, 10);
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; ++i) {
            if (i == center) continue;
            edges.push_back({center, i});
        }
    } else if (type == 3) {
        // Simple cycle (odd or even) with a few isolated vertices
        int lenCandidates[] = {3,4,5,6,7,8,9,10};
        int len = lenCandidates[rnd.next(0, 8)];
        int extra = rnd.next(0, 3);
        N = len + extra;
        for (int i = 1; i < len; ++i)
            edges.push_back({i, i + 1});
        edges.push_back({len, 1});
    } else if (type == 4) {
        // Triangle plus tail
        N = rnd.next(4, 10);
        edges.push_back({1, 2});
        edges.push_back({2, 3});
        edges.push_back({3, 1});
        for (int v = 4; v <= N; ++v)
            edges.push_back({v - 1, v});
    } else if (type == 5) {
        // Multiple components: mix of paths, stars, cycles, isolated vertices
        N = rnd.next(5, 12);
        int comps = rnd.next(2, 4);
        int cur = 1;
        int remaining = N;
        for (int c = 1; c <= comps; ++c) {
            int compSize;
            if (c == comps) {
                compSize = remaining;
            } else {
                compSize = rnd.next(1, remaining - (comps - c));
            }
            int offset = cur;
            if (compSize == 1) {
                // isolated vertex
            } else if (compSize == 2) {
                bool addEdge = (rnd.next(0, 1) == 1);
                if (addEdge)
                    edges.push_back({offset, offset + 1});
            } else {
                int kind = rnd.next(0, 2); // 0=path,1=star,2=cycle
                if (kind == 0) {
                    // Path
                    for (int i = 0; i < compSize - 1; ++i)
                        edges.push_back({offset + i, offset + i + 1});
                } else if (kind == 1) {
                    // Star
                    int center = offset;
                    for (int i = 1; i < compSize; ++i)
                        edges.push_back({center, offset + i});
                } else {
                    // Cycle
                    for (int i = 0; i < compSize - 1; ++i)
                        edges.push_back({offset + i, offset + i + 1});
                    edges.push_back({offset + compSize - 1, offset});
                }
            }
            cur += compSize;
            remaining -= compSize;
        }
    } else if (type == 6) {
        // Random sparse simple graph
        N = rnd.next(5, 12);
        vector<pair<int,int>> allEdges;
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                allEdges.push_back({i, j});
        shuffle(allEdges.begin(), allEdges.end());
        int limitE = min((int)allEdges.size(), N + 2);
        int targetE = rnd.next(1, limitE);
        edges.assign(allEdges.begin(), allEdges.begin() + targetE);
    } else if (type == 7) {
        // Random medium-density simple graph
        N = rnd.next(8, 15);
        vector<pair<int,int>> allEdges;
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                allEdges.push_back({i, j});
        shuffle(allEdges.begin(), allEdges.end());
        int maxEdges = (int)allEdges.size();
        int high = min(maxEdges, 70);
        int low = max(1, high / 2);
        if (low > high) low = high;
        int targetE = rnd.next(low, high);
        edges.assign(allEdges.begin(), allEdges.begin() + targetE);
    } else if (type == 8) {
        // Connected graph where every vertex has degree at least 2
        int baseLen = rnd.next(3, 10);
        int extra = rnd.next(0, 3);
        N = baseLen + extra;

        set<pair<int,int>> used;

        auto addEdge = [&](int u, int v) {
            if (u > v) swap(u, v);
            if (u == v) return;
            if (used.insert({u, v}).second)
                edges.push_back({u, v});
        };

        // Base cycle
        for (int i = 1; i < baseLen; ++i)
            addEdge(i, i + 1);
        addEdge(baseLen, 1);

        // Attach extra vertices with degree 2
        for (int v = baseLen + 1; v <= N; ++v) {
            int a = rnd.next(1, v - 1);
            int b = rnd.next(1, v - 1);
            while (b == a) b = rnd.next(1, v - 1);
            addEdge(v, a);
            addEdge(v, b);
        }

        // Add a few random chords
        int attempts = rnd.next(0, N);
        for (int k = 0; k < attempts && (int)edges.size() < 70; ++k) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) continue;
            addEdge(u, v);
        }
    } else if (type == 9) {
        // Random tree
        N = rnd.next(2, 20);
        for (int v = 2; v <= N; ++v) {
            int p = rnd.next(1, v - 1);
            edges.push_back({p, v});
        }
    }

    // Safety: ensure at least one edge
    if (edges.empty()) {
        if (N < 2) N = 2;
        edges.push_back({1, 2});
    }

    // Optional random permutation of vertex labels
    bool doPermute = (rnd.next(0, 1) == 1);
    if (doPermute) {
        vector<int> perm(N);
        for (int i = 0; i < N; ++i) perm[i] = i + 1;
        shuffle(perm.begin(), perm.end());
        for (auto &e : edges) {
            e.first = perm[e.first - 1];
            e.second = perm[e.second - 1];
        }
    }

    // Optional shuffle of edge order
    if (rnd.next(0, 1) == 1) {
        shuffle(edges.begin(), edges.end());
    }

    println(N, (int)edges.size());
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
