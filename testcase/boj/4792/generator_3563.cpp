#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; ++tc) {
        int n = rnd.next(2, 10);
        int totalPairs = n * (n - 1) / 2;
        int extraMax = totalPairs - (n - 1);
        int extra = extraMax > 0 ? rnd.next(0, extraMax) : 0;
        int m = (n - 1) + extra;
        int k = rnd.next(0, n - 1);
        println(n, m, k);

        // Build a random spanning tree
        vector<pair<int,int>> edges;
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        for (int i = 1; i < n; ++i) {
            int u = nodes[i];
            int v = nodes[rnd.next(0, i - 1)];
            edges.emplace_back(u, v);
        }

        // Gather all possible remaining edges
        vector<pair<int,int>> avail;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                avail.emplace_back(i, j);
            }
        }
        // Remove tree edges from avail
        for (auto &e : edges) {
            int u = min(e.first, e.second), v = max(e.first, e.second);
            for (auto it = avail.begin(); it != avail.end(); ++it) {
                if (it->first == u && it->second == v) {
                    avail.erase(it);
                    break;
                }
            }
        }
        // Add extra edges
        shuffle(avail.begin(), avail.end());
        for (int i = 0; i < extra; ++i) {
            edges.push_back(avail[i]);
        }

        // Shuffle final edge list and assign colors
        shuffle(edges.begin(), edges.end());
        double blueProb = rnd.next(0.0, 1.0);
        for (auto &e : edges) {
            char c = (rnd.next() < blueProb ? 'B' : 'R');
            println(c, e.first, e.second);
        }
    }
    // Terminator
    println(0, 0, 0);
    return 0;
}
