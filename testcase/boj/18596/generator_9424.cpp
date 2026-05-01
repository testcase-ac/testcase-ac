#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 2);
    println(T);

    bool usedSpecial = false;

    for (int tc = 1; tc <= T; ++tc) {
        int n;
        vector<int> a, b;
        vector<pair<int,int>> edges;

        // With some probability, use a hand-crafted tricky test
        if (!usedSpecial && rnd.next(0, 3) == 0) {
            usedSpecial = true;
            n = 4;
            a.assign(n + 1, 0);
            b.assign(n + 1, 0);
            // Monsters at nodes 2..4 (star centered at 1)
            // Node 2: heavy loss, no reward
            a[2] = 8;  b[2] = 0;
            // Node 3: moderate loss, big reward
            a[3] = 3;  b[3] = 10;
            // Node 4: neutral
            a[4] = 4;  b[4] = 4;

            edges.push_back({1, 2});
            edges.push_back({1, 3});
            edges.push_back({1, 4});
        } else {
            // Random small tree with various structures
            int pattern = rnd.next(0, 2); // 0: path, 1: star, 2: random
            // Keep n small for readability
            if (pattern == 0) {
                n = rnd.next(2, 7); // path
            } else if (pattern == 1) {
                n = rnd.next(3, 7); // star
            } else {
                n = rnd.next(4, 7); // general random
            }

            a.assign(n + 1, 0);
            b.assign(n + 1, 0);

            // Generate monster stats for vertices 2..n
            for (int i = 2; i <= n; ++i) {
                int style = rnd.next(0, 4);
                int aa = 0, bb = 0;
                if (style == 0) {
                    // Small numbers, non-negative net gain
                    aa = rnd.next(0, 5);
                    bb = aa + rnd.next(0, 5);
                } else if (style == 1) {
                    // Lossy nodes (net negative)
                    aa = rnd.next(1, 8);
                    bb = rnd.next(0, aa - 1);
                } else if (style == 2) {
                    // Balanced nodes (zero net)
                    aa = rnd.next(0, 8);
                    bb = aa;
                } else if (style == 3) {
                    // Free reward
                    aa = 0;
                    bb = rnd.next(1, 8);
                } else {
                    // Large values to test overflow / big numbers
                    int choices[4] = {0, 1, 1000000000, 999999999};
                    aa = choices[rnd.next(0, 3)];
                    bb = choices[rnd.next(0, 3)];
                }
                a[i] = aa;
                b[i] = bb;
            }

            // Build tree structure
            if (pattern == 0) {
                // Path: 1-2-3-...-n
                for (int i = 2; i <= n; ++i) {
                    edges.push_back({i - 1, i});
                }
            } else if (pattern == 1) {
                // Star centered at 1
                for (int i = 2; i <= n; ++i) {
                    edges.push_back({1, i});
                }
            } else {
                // Random tree: connect each node i to a random previous node
                for (int i = 2; i <= n; ++i) {
                    int p = rnd.next(1, i - 1);
                    edges.push_back({p, i});
                }
            }

            // Shuffle edges and possibly swap endpoints to randomize
            shuffle(edges.begin(), edges.end());
            for (auto &e : edges) {
                if (rnd.next(0, 1)) swap(e.first, e.second);
            }
        }

        // Output test case
        println(n);
        for (int i = 2; i <= n; ++i) {
            println(a[i], b[i]);
        }
        for (auto &e : edges) {
            println(e.first, e.second);
        }
    }

    return 0;
}
