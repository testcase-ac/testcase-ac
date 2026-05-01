#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes
    int N = rnd.next(2, 10);
    // Node weights up to Amax
    int Amax = rnd.next(1, 20);
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        A[i] = rnd.next(1, Amax);
    }
    // Choose distinct S, T
    int S = rnd.next(1, N), T;
    do {
        T = rnd.next(1, N);
    } while (T == S);
    // Decide if a path exists; force true when N<=2 to allow M>=2
    bool hasPath = true;
    if (N > 2) hasPath = rnd.next(0, 3) != 0; // ~75% chance true
    // Build base path edges if needed
    vector<pair<int,int>> baseEdges;
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    if (hasPath) {
        int K = rnd.next(2, N);
        vector<int> cands;
        for (int i = 1; i <= N; i++) {
            if (i != S && i != T) cands.push_back(i);
        }
        shuffle(cands.begin(), cands.end());
        cands.resize(max(0, K - 2));
        vector<int> path;
        path.push_back(S);
        for (int x : cands) path.push_back(x);
        path.push_back(T);
        for (int i = 0; i + 1 < (int)path.size(); i++) {
            int u = path[i], v = path[i+1];
            baseEdges.emplace_back(u, v);
            used[u][v] = true;
        }
    }
    // Pool of other possible edges
    vector<pair<int,int>> pool;
    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            if (u == v) continue;
            if (used[u][v]) continue;
            if (!hasPath && v == T) continue;
            pool.emplace_back(u, v);
        }
    }
    shuffle(pool.begin(), pool.end());
    int EP = pool.size();
    int t = rnd.next(-2, 2);
    int add = 0;
    if (EP > 0) {
        add = rnd.wnext(EP, t);
    }
    // Ensure at least 2 edges total
    int needed = max(0, 2 - (int)baseEdges.size() - add);
    add += needed;
    if (add > EP) add = EP;
    vector<pair<int,int>> edges = baseEdges;
    for (int i = 0; i < add; i++) {
        edges.push_back(pool[i]);
    }
    int M = edges.size();
    // Edge weight hyper-parameters
    int Wmax = rnd.next(1, 20);
    int tW = rnd.next(-2, 2);
    // Output
    println(N, M);
    vector<int> Aout(A.begin() + 1, A.end());
    println(Aout);
    println(S, T);
    for (auto &e : edges) {
        int w;
        if (Wmax > 1) w = rnd.wnext(Wmax - 1, tW) + 1;
        else w = 1;
        println(e.first, e.second, w);
    }
    return 0;
}
