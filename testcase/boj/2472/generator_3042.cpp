#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Number of nodes (store candidates)
    int n = rnd.next(3, 10);

    // Track connectivity and degrees
    vector<vector<bool>> conn(n + 1, vector<bool>(n + 1, false));
    vector<int> deg(n + 1, 0);
    vector<tuple<int,int,int>> edges;

    // 2) Build a random spanning tree ensuring degree ≤ 5
    for (int i = 2; i <= n; i++) {
        vector<int> cand;
        for (int j = 1; j < i; j++) {
            if (deg[j] < 5) cand.push_back(j);
        }
        if (cand.empty()) {
            for (int j = 1; j < i; j++) cand.push_back(j);
        }
        int p = rnd.any(cand);
        int w = rnd.next(1, 10);
        edges.emplace_back(p, i, w);
        conn[p][i] = conn[i][p] = true;
        deg[p]++; deg[i]++;
    }

    // 3) Collect candidate non-tree edges under degree limit
    vector<pair<int,int>> extras;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!conn[i][j] && deg[i] < 5 && deg[j] < 5)
                extras.emplace_back(i, j);
        }
    }

    // 4) Decide how many extra edges to add (cap total edges ≤ 20)
    int maxAdd = min((int)extras.size(), max(0, 20 - (int)edges.size()));
    int extraCount = 0;
    if (maxAdd > 0) {
        int t = rnd.next(-1, 1);
        extraCount = rnd.wnext(maxAdd + 1, t);
    }

    // 5) Shuffle candidates and pick extras respecting degree ≤ 5
    shuffle(extras.begin(), extras.end());
    for (auto &pr : extras) {
        if ((int)edges.size() >= 20) break;
        if (extraCount == 0) break;
        int u = pr.first, v = pr.second;
        if (deg[u] < 5 && deg[v] < 5) {
            int w = rnd.next(1, 10);
            edges.emplace_back(u, v, w);
            deg[u]++; deg[v]++;
            extraCount--;
        }
    }

    // 6) Final shuffle of edges
    shuffle(edges.begin(), edges.end());
    int m = edges.size();

    // 7) Pick three distinct apartment locations A, B, C
    vector<int> ids(n);
    for (int i = 0; i < n; i++) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());
    int A = ids[0], B = ids[1], C = ids[2];

    // 8) Generate queries
    int T = rnd.next(1, n);
    vector<int> queries(T);
    for (int i = 0; i < T; i++) {
        queries[i] = rnd.next(1, n);
    }

    // 9) Output everything
    println(n);
    println(A, B, C);
    println(m);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    println(T);
    for (int q : queries) {
        println(q);
    }

    return 0;
}
