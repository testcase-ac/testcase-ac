#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Number of houses
        int m = rnd.next(2, 10);
        // Maximum possible edges
        int maxE = m * (m - 1) / 2;
        // Decide how many extra edges beyond the spanning tree
        int maxExtra = maxE - (m - 1);
        int skew = rnd.any(vector<int>{-1, 1});
        // wnext(hi, skew): hi = maxExtra+1, gives [0..maxExtra]
        int extra = rnd.wnext(maxExtra + 1, skew);
        int n = (m - 1) + extra;

        // Generate a random spanning tree to ensure connectivity
        vector<pair<int,int>> treeEdges;
        for (int i = 1; i < m; i++) {
            int j = rnd.next(0, i - 1);
            treeEdges.emplace_back(i, j);
        }
        // Prepare all possible non-tree edges
        vector<pair<int,int>> nonTree;
        vector<vector<bool>> used(m, vector<bool>(m, false));
        for (auto &e : treeEdges) {
            used[e.first][e.second] = used[e.second][e.first] = true;
        }
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                if (!used[i][j]) nonTree.emplace_back(i, j);
            }
        }
        shuffle(nonTree.begin(), nonTree.end());
        // Take the required extra edges
        vector<pair<int,int>> edges = treeEdges;
        for (int i = 0; i < extra && i < (int)nonTree.size(); i++) {
            edges.push_back(nonTree[i]);
        }

        // Decide weight distribution parameters
        int R = rnd.any(vector<int>{10, 50, 100});
        int wtSkew = rnd.any(vector<int>{-1, 1});

        // Output this test
        println(m, n);
        for (auto &e : edges) {
            int w = rnd.wnext(R, wtSkew) + 1; // in [1..R]
            println(e.first, e.second, w);
        }
    }
    // Termination line
    println(0, 0);
    return 0;
}
