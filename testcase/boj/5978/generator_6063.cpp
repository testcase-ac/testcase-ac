#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Choose N in [2,10]
    int N = rnd.next(2, 10);

    // 2) Decide if we want a "possible" instance (all components even sized) or "impossible"
    bool possible = rnd.next(0, 1) == 1 && (N % 2 == 0);

    // 3) Partition N into component sizes
    vector<int> compSizes;
    if (possible) {
        // All parts even, sum = N (which is even)
        int maxC = min(N/2, 3);
        int C = rnd.next(1, maxC);
        // We need C parts, each at least 2, sum to N, all even.
        // Let xi = compSizes[i]/2, sum xi = N/2, xi >= 1
        int S = N/2 - C; // remainder to distribute to xi after each has 1
        vector<int> addon(C, 0);
        for (int i = 0; i < C; ++i) {
            int take = (i == C-1 ? S : rnd.next(0, S));
            addon[i] = take;
            S -= take;
        }
        compSizes.resize(C);
        for (int i = 0; i < C; ++i) {
            compSizes[i] = 2 * (1 + addon[i]);
        }
    } else {
        // Impossible: at least one component has odd size
        int maxC = min(N, 3);
        int C = rnd.next(1, maxC);
        // Random positive partition into C parts
        set<int> cuts;
        while ((int)cuts.size() < C-1) {
            cuts.insert(rnd.next(1, N-1));
        }
        vector<int> pts;
        pts.push_back(0);
        for (int x : cuts) pts.push_back(x);
        pts.push_back(N);
        sort(pts.begin(), pts.end());
        compSizes.resize(C);
        for (int i = 0; i < C; ++i) {
            compSizes[i] = pts[i+1] - pts[i];
        }
        // Ensure at least one odd part
        bool hasOdd = false;
        for (int x : compSizes) if (x % 2 == 1) { hasOdd = true; break; }
        if (!hasOdd) {
            // adjust between first two parts
            if (C >= 2 && compSizes[1] > 1) {
                compSizes[0] += 1; compSizes[1] -= 1;
            } else if (C >= 2 && compSizes[0] > 1) {
                compSizes[0] -= 1; compSizes[1] += 1;
            } else {
                // fallback: make first part odd by merging second
                if (C >= 2) {
                    compSizes[0] += compSizes[1];
                    compSizes.erase(compSizes.begin()+1);
                }
            }
        }
        // If all parts are size 1, merge first two into size>=2
        bool anyBig = false;
        for (int x : compSizes) if (x >= 2) anyBig = true;
        if (!anyBig && (int)compSizes.size() >= 2) {
            compSizes[0] += compSizes[1];
            compSizes.erase(compSizes.begin()+1);
        }
    }

    // 4) Build edges: first a spanning tree (path or star) for each component
    vector<pair<int,int>> edges;
    int cur = 1;
    for (int sz : compSizes) {
        vector<int> verts(sz);
        for (int i = 0; i < sz; i++) verts[i] = cur + i;
        cur += sz;
        if (sz < 2) continue;
        // choose a random tree shape: path or star
        if (rnd.next(0,1) == 0) {
            // path
            for (int i = 0; i+1 < sz; i++) {
                edges.emplace_back(verts[i], verts[i+1]);
            }
        } else {
            // star
            int center = rnd.any(verts);
            for (int v : verts) if (v != center) {
                edges.emplace_back(center, v);
            }
        }
    }

    // 5) Prepare all possible edges within each component
    set<pair<int,int>> have;
    for (auto &e : edges) {
        int a = e.first, b = e.second;
        if (a > b) swap(a,b);
        have.insert({a,b});
    }
    vector<pair<int,int>> allExtras;
    cur = 1;
    for (int sz : compSizes) {
        vector<int> verts(sz);
        for (int i = 0; i < sz; i++) verts[i] = cur + i;
        cur += sz;
        for (int i = 0; i < sz; i++) {
            for (int j = i+1; j < sz; j++) {
                int a = verts[i], b = verts[j];
                int x = a, y = b;
                if (x > y) swap(x,y);
                if (!have.count({x,y})) {
                    allExtras.emplace_back(a,b);
                }
            }
        }
    }

    // 6) Decide final M in [initialEdges, initialEdges + extras]
    int E0 = edges.size();
    int Emax = E0 + allExtras.size();
    int M = rnd.next(E0, Emax);

    // 7) Add extra edges up to M
    shuffle(allExtras.begin(), allExtras.end());
    for (int i = 0; i < M - E0; i++) {
        edges.push_back(allExtras[i]);
    }

    // 8) Shuffle final edge order for variety
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
