#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of nodes N: between 5 and 15, skewable
    vector<int> tvals_N = {-2, -1, 0, 1, 2};
    int tN = rnd.any(tvals_N);
    int N = rnd.wnext(11, tN) + 5; // 11 = 15-5+1, so N in [5,15]

    // Compute maximum possible edges
    int maxEdges = N * (N - 1) / 2;

    // Hyper-parameter: ensure connected or allow disconnected
    bool conn = rnd.next(0, 1) == 1;

    // Hyper-parameter for extra edges distribution
    vector<int> tvals_M = {-2, -1, 0, 1, 2};
    int tM = rnd.any(tvals_M);

    int M_min = conn ? (N - 1) : 1;
    int hi_extra = maxEdges - M_min + 1; // for wnext
    int extra = rnd.wnext(hi_extra, tM);
    int M = M_min + extra;

    // Hyper-parameter for start vertex R
    vector<int> tvals_R = {-2, -1, 0, 1, 2};
    int tR = rnd.any(tvals_R);
    int R = rnd.wnext(N, tR) + 1; // in [1, N]

    // Prepare edges
    vector<pair<int,int>> edges;
    if (conn) {
        // Build a random spanning tree first
        vector<int> order(N);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        for (int i = 1; i < N; i++) {
            int u = order[i];
            int idx = rnd.next(0, i-1);
            int v = order[idx];
            int a = min(u, v), b = max(u, v);
            edges.emplace_back(a, b);
            used[a][b] = used[b][a] = true;
        }
        // Collect remaining candidate edges
        vector<pair<int,int>> cand;
        for (int u = 1; u <= N; u++) {
            for (int v = u + 1; v <= N; v++) {
                if (!used[u][v]) cand.emplace_back(u, v);
            }
        }
        shuffle(cand.begin(), cand.end());
        // Add extra edges
        for (int i = 0; i < extra; i++) {
            edges.push_back(cand[i]);
        }
    } else {
        // No connectivity requirement, pick any M edges
        vector<pair<int,int>> cand;
        for (int u = 1; u <= N; u++) {
            for (int v = u + 1; v <= N; v++) {
                cand.emplace_back(u, v);
            }
        }
        shuffle(cand.begin(), cand.end());
        edges.assign(cand.begin(), cand.begin() + M);
    }

    // Final shuffle of edge list for variability
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M, R);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
