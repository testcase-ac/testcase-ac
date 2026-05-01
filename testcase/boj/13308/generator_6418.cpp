#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 12);
    // Graph type: 0 = chain, 1 = star, 2 = random tree, 3 = random tree + extra edges
    int graphType = rnd.next(0, 3);

    vector<tuple<int,int,int>> edges;

    if (graphType == 0) {
        // Simple chain: 1-2, 2-3, ..., (N-1)-N
        for (int i = 1; i < N; i++) {
            int w = rnd.next(1, 20);
            edges.emplace_back(i, i+1, w);
        }
    } else if (graphType == 1) {
        // Star centered at c
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == c) continue;
            int w = rnd.next(1, 20);
            edges.emplace_back(c, i, w);
        }
    } else {
        // Generate a random spanning tree
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        set<pair<int,int>> used;
        for (int i = 1; i < N; i++) {
            int j = rnd.next(0, i-1);
            int u = nodes[i], v = nodes[j];
            if (u > v) swap(u, v);
            int w = rnd.next(1, 20);
            edges.emplace_back(u, v, w);
            used.insert({u, v});
        }
        // If graphType == 3, add some extra random edges
        if (graphType == 3) {
            int maxExtra = N*(N-1)/2 - (N-1);
            if (maxExtra >= 1) {
                int extra = rnd.next(1, min(maxExtra, N));
                vector<pair<int,int>> cand;
                for (int u = 1; u <= N; u++) {
                    for (int v = u+1; v <= N; v++) {
                        if (!used.count({u, v}))
                            cand.emplace_back(u, v);
                    }
                }
                shuffle(cand.begin(), cand.end());
                for (int i = 0; i < extra && i < (int)cand.size(); i++) {
                    int u = cand[i].first, v = cand[i].second;
                    int w = rnd.next(1, 20);
                    edges.emplace_back(u, v, w);
                }
            }
        }
    }

    int M = edges.size();

    // Prices at each city
    vector<int> price(N);
    // 0 = all 1, 1 = random, 2 = sorted asc, 3 = sorted desc
    int pType = rnd.next(0, 3);
    if (pType == 0) {
        for (int &x : price) x = 1;
    } else if (pType == 1) {
        for (int &x : price) x = rnd.next(1, 20);
    } else {
        for (int &x : price) x = rnd.next(1, 20);
        sort(price.begin(), price.end());
        if (pType == 3) reverse(price.begin(), price.end());
    }
    // Occasionally force extremes at endpoints
    if (rnd.next(0, 4) == 0) price[0] = *max_element(price.begin(), price.end());
    if (rnd.next(0, 4) == 0) price[N-1] = *min_element(price.begin(), price.end());

    // Output
    println(N, M);
    println(price);
    shuffle(edges.begin(), edges.end());
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    return 0;
}
