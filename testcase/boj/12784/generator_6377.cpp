#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of islands (nodes)
        int N = rnd.next(2, 10);
        int M = N - 1;

        // Build a tree rooted at 1 with different shapes
        int treeType = rnd.next(0, 3);
        vector<int> parent(N + 1, 0);
        parent[1] = 0;
        if (treeType == 0) {
            // Chain: 1-2-3-...-N
            for (int i = 2; i <= N; i++)
                parent[i] = i - 1;
        } else if (treeType == 1) {
            // Star: all connect to 1
            for (int i = 2; i <= N; i++)
                parent[i] = 1;
        } else if (treeType == 2) {
            // Random tree: parent[i] is random from [1..i-1]
            for (int i = 2; i <= N; i++)
                parent[i] = rnd.next(1, i - 1);
        } else {
            // BFS-like balanced tree
            vector<int> q;
            q.push_back(1);
            int qi = 0;
            for (int i = 2; i <= N; i++) {
                parent[i] = q[qi];
                q.push_back(i);
                qi = (qi + 1) % (int)q.size();
            }
        }

        // Collect edges
        vector<pair<int,int>> edges;
        for (int i = 2; i <= N; i++)
            edges.emplace_back(parent[i], i);
        // Shuffle edge order for variability
        shuffle(edges.begin(), edges.end());

        // Choose weight-distribution type
        int wType = rnd.next(0, 2);
        // Output
        println(N, M);
        for (auto &e : edges) {
            int w;
            if (wType == 0) {
                w = rnd.next(1, 20);
            } else if (wType == 1) {
                // bias towards small weights
                w = rnd.wnext(20, -1) + 1;
            } else {
                // bias towards large weights
                w = rnd.wnext(20, 1) + 1;
            }
            println(e.first, e.second, w);
        }
    }

    return 0;
}
