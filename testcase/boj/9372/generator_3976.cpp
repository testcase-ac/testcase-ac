#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 7);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of nodes
        int N = rnd.next(2, 10);
        // Maximum possible edges
        int maxEdges = N * (N - 1) / 2;
        // Extra edges beyond the spanning tree
        int extraMax = maxEdges - (N - 1);
        // Weighted choice for extra edge count to vary density
        int t = rnd.next(-2, 2);
        int E = (extraMax > 0 ? rnd.wnext(extraMax + 1, t) : 0);
        int M = (N - 1) + E;

        // Build a random spanning tree first
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        vector<pair<int,int>> edges;
        edges.reserve(M);
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        for (int i = 1; i < N; i++) {
            int u = nodes[i];
            int v = nodes[rnd.next(0, i - 1)];
            edges.emplace_back(u, v);
            int a = min(u, v), b = max(u, v);
            used[a][b] = true;
        }
        // Collect remaining possible edges
        vector<pair<int,int>> pool;
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (!used[i][j]) {
                    pool.emplace_back(i, j);
                }
            }
        }
        shuffle(pool.begin(), pool.end());
        // Add extra edges
        for (int i = 0; i < E && i < (int)pool.size(); i++) {
            edges.push_back(pool[i]);
        }
        // Shuffle edge order for output
        shuffle(edges.begin(), edges.end());

        // Output this test case
        println(N, M);
        for (auto &e : edges) {
            println(e.first, e.second);
        }
    }
    return 0;
}
