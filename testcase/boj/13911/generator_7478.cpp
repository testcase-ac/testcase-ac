#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int V = rnd.next(3, 12);
    vector<int> nodes(V);
    iota(nodes.begin(), nodes.end(), 1);

    // Choose McDonald's locations
    int M = rnd.next(1, V - 2);
    vector<int> perm = nodes;
    shuffle(perm.begin(), perm.end());
    vector<int> mpos(perm.begin(), perm.begin() + M);

    // Choose Starbucks locations, ensure at least one house remains
    int S = rnd.next(1, V - 2);
    vector<int> spos;
    while (true) {
        perm = nodes;
        shuffle(perm.begin(), perm.end());
        spos.assign(perm.begin(), perm.begin() + S);
        vector<bool> used(V + 1, false);
        for (int x : mpos) used[x] = true;
        for (int x : spos) used[x] = true;
        int cnt = 0;
        for (int i = 1; i <= V; i++) if (!used[i]) cnt++;
        if (cnt > 0) break;
    }

    // Possible edges
    int maxEdges = V * (V - 1) / 2;
    int E = rnd.next(0, maxEdges);
    vector<pair<int,int>> cand;
    for (int i = 1; i <= V; i++)
        for (int j = i + 1; j <= V; j++)
            cand.emplace_back(i, j);
    shuffle(cand.begin(), cand.end());
    cand.resize(E);

    // Edge weights
    vector<tuple<int,int,int>> edges;
    vector<int> wchoices = {10, 50, 100};
    int wmax = rnd.any(wchoices);
    for (auto &p : cand) {
        int w = rnd.next(1, wmax);
        edges.emplace_back(p.first, p.second, w);
    }

    // Distance thresholds
    long long x, y;
    if (rnd.next(0, 1) == 0)
        x = rnd.next(1, wmax);
    else
        x = rnd.next((long long)wmax, (long long)wmax * V);
    if (rnd.next(0, 1) == 0)
        y = rnd.next(1, wmax);
    else
        y = rnd.next((long long)wmax, (long long)wmax * V);

    // Output
    println(V, E);
    for (auto &t : edges)
        println(get<0>(t), get<1>(t), get<2>(t));
    println(M, x);
    println(mpos);
    println(S, y);
    println(spos);

    return 0;
}
