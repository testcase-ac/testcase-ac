#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 1; tc <= T; ++tc) {
        int M = rnd.next(2, 12);
        int totalEdges = M * (M - 1) / 2;
        int treeEdgesCount = M - 1;
        int extraMax = totalEdges - treeEdgesCount;
        vector<int> vSkew = { -2, -1, 0, 1, 2 };
        int skew = rnd.any(vSkew);
        int extra = rnd.wnext(extraMax + 1, skew);
        int P = treeEdgesCount + extra;

        // Build a random topological order with M at the end
        vector<int> topo;
        topo.reserve(M);
        for (int i = 1; i < M; ++i) topo.push_back(i);
        shuffle(topo.begin(), topo.end());
        topo.push_back(M);

        // Generate a spanning arborescence towards M to ensure connectivity
        vector<vector<bool>> used(M + 1, vector<bool>(M + 1, false));
        vector<pair<int,int>> edges;
        edges.reserve(P);
        for (int i = 0; i < M - 1; ++i) {
            int j = rnd.next(i + 1, M - 1);
            int u = topo[i], v = topo[j];
            edges.emplace_back(u, v);
            used[u][v] = true;
        }

        // Collect remaining possible edges and pick extras
        vector<pair<int,int>> possible;
        for (int i = 0; i < M; ++i) {
            for (int j = i + 1; j < M; ++j) {
                int u = topo[i], v = topo[j];
                if (!used[u][v]) possible.emplace_back(u, v);
            }
        }
        shuffle(possible.begin(), possible.end());
        for (int i = 0; i < extra; ++i) {
            edges.push_back(possible[i]);
        }

        // Shuffle edge order for variability
        shuffle(edges.begin(), edges.end());

        // Output this test case
        println(tc, M, P);
        for (auto &e : edges) println(e.first, e.second);
    }
    return 0;
}
