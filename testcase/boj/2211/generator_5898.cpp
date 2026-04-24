#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of computers
    int N = rnd.next(2, 15);
    // Maximum possible edges
    int maxM = N * (N - 1) / 2;
    // Limit extra edges to keep input small
    int maxExtra = maxM - (N - 1);
    maxExtra = min(maxExtra, 20);
    int extra = maxExtra > 0 ? rnd.next(0, maxExtra) : 0;
    int M = (N - 1) + extra;

    vector<tuple<int,int,int>> edges;
    // Build a random spanning tree to ensure connectivity
    for (int i = 2; i <= N; i++) {
        int j = rnd.next(1, i - 1);
        int t = rnd.next(-2, 2);
        int w = 1 + rnd.wnext(10, t);
        edges.emplace_back(j, i, w);
    }

    // Track used pairs
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (auto &e : edges) {
        int a = get<0>(e), b = get<1>(e);
        used[a][b] = used[b][a] = true;
    }
    // Collect all remaining pairs
    vector<pair<int,int>> pool;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            if (!used[i][j])
                pool.emplace_back(i, j);

    // Shuffle and pick extra edges
    shuffle(pool.begin(), pool.end());
    for (int k = 0; k < extra && k < (int)pool.size(); k++) {
        int a = pool[k].first, b = pool[k].second;
        int t = rnd.next(-2, 2);
        int w = 1 + rnd.wnext(10, t);
        edges.emplace_back(a, b, w);
    }

    // Randomize edge order for output
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }
    return 0;
}
