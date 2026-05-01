#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of PCs
    int N = rnd.next(1, 15);
    // Number of seeds allowed
    int K = rnd.next(1, N);
    // Number of components
    int c = rnd.wnext(N, -1); // more small components bias
    c = max(1, min(c, N));
    // Partition N into c positive sizes
    vector<int> compSizes(c, 1);
    for (int i = 0; i < N - c; i++) {
        int idx = rnd.next(0, c-1);
        compSizes[idx]++;
    }
    // Assign nodes to components
    vector<vector<int>> comps(c);
    int cur = 1;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < compSizes[i]; j++) {
            comps[i].push_back(cur++);
        }
    }
    // Generate a_i times
    vector<int> a(N+1);
    for (int i = 1; i <= N; i++) {
        a[i] = rnd.next(1, 100);
    }
    // Build edges per component
    vector<array<int,3>> edges;
    for (int i = 0; i < c; i++) {
        auto v = comps[i];
        int sz = (int)v.size();
        if (sz >= 2) {
            // spanning tree
            vector<int> ord = v;
            shuffle(ord.begin(), ord.end());
            set<pair<int,int>> used;
            for (int j = 1; j < sz; j++) {
                int p = rnd.next(0, j-1);
                int x = ord[j], y = ord[p];
                if (x > y) swap(x,y);
                used.insert({x,y});
                edges.push_back({ord[j], ord[p], rnd.next(1,100)});
            }
            // extra edges up to 3
            int maxPairs = sz*(sz-1)/2;
            int remaining = maxPairs - (sz-1);
            int extra = remaining > 0 ? rnd.next(0, min(remaining, 3)) : 0;
            // collect all non-tree pairs
            vector<pair<int,int>> cand;
            for (int p1 = 0; p1 < sz; p1++) {
                for (int p2 = p1+1; p2 < sz; p2++) {
                    int x = v[p1], y = v[p2];
                    int xx = x, yy = y;
                    if (xx > yy) swap(xx,yy);
                    if (!used.count({xx,yy})) {
                        cand.emplace_back(x,y);
                    }
                }
            }
            shuffle(cand.begin(), cand.end());
            for (int j = 0; j < extra && j < (int)cand.size(); j++) {
                edges.push_back({cand[j].first, cand[j].second, rnd.next(1,100)});
            }
        }
    }
    // Shuffle all edges
    shuffle(edges.begin(), edges.end());
    int M = (int)edges.size();
    // Output
    println(N, M, K);
    for (int i = 1; i <= N; i++) printf("%d%c", a[i], i==N?'\n':' ');
    for (auto &e : edges) {
        println(e[0], e[1], e[2]);
    }
    return 0;
}
