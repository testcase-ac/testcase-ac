#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand verification
    int N = rnd.next(2, 10);
    // Generate permutation p: identity with ~10% prob, else random non-identity
    vector<int> p(N);
    iota(p.begin(), p.end(), 1);
    if (rnd.next(0, 9) != 0) {
        bool isIdentity;
        do {
            shuffle(p.begin(), p.end());
            isIdentity = true;
            for (int i = 0; i < N; i++) {
                if (p[i] != i + 1) { isIdentity = false; break; }
            }
        } while (isIdentity);
    }
    // Decompose cycles in p
    vector<bool> used(N, false);
    vector<vector<int>> cycles;
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            int x = i;
            vector<int> cyc;
            while (!used[x]) {
                used[x] = true;
                cyc.push_back(x + 1);
                x = p[x] - 1;
            }
            if (cyc.size() >= 2) cycles.push_back(cyc);
        }
    }
    // All possible pairs
    vector<pair<int,int>> allPairs;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            allPairs.emplace_back(i, j);
    set<pair<int,int>> usedEdges;
    vector<tuple<int,int,int>> edges;
    // Build required edges to allow sorting: connect each cycle
    if (!cycles.empty()) {
        int t;
        if (rnd.next(0,1) == 0) t = rnd.next(1, 10);
        else t = rnd.next(90, 100);
        vector<pair<int,int>> cyclePairs;
        for (auto &c : cycles) {
            shuffle(c.begin(), c.end());
            for (int i = 0; i + 1 < (int)c.size(); i++) {
                int a = c[i], b = c[i+1];
                if (a > b) swap(a, b);
                cyclePairs.emplace_back(a, b);
            }
        }
        int idx0 = rnd.next(0, (int)cyclePairs.size() - 1);
        for (int i = 0; i < (int)cyclePairs.size(); i++) {
            int a = cyclePairs[i].first;
            int b = cyclePairs[i].second;
            int w = (i == idx0 ? t : rnd.next(t, 100));
            edges.emplace_back(a, b, w);
            usedEdges.insert({a, b});
        }
    }
    // Add extra random edges
    int maxExtra = (int)allPairs.size() - (int)usedEdges.size();
    int K;
    if (edges.empty()) {
        K = rnd.next(1, maxExtra);
    } else {
        K = rnd.next(0, min(maxExtra, N));
    }
    vector<pair<int,int>> avail;
    for (auto &pr : allPairs) {
        if (!usedEdges.count(pr)) avail.push_back(pr);
    }
    shuffle(avail.begin(), avail.end());
    for (int i = 0; i < K; i++) {
        int a = avail[i].first, b = avail[i].second;
        int w = rnd.next(1, 100);
        edges.emplace_back(a, b, w);
    }
    // Shuffle all edges for variability
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    // Output
    println(N, M);
    println(p);
    for (auto &e : edges) {
        int a, b, w;
        tie(a, b, w) = e;
        println(a, b, w);
    }
    return 0;
}
