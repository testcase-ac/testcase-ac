#include "testlib.h"
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (will end with a trailing 0)
    int T = rnd.next(3, 6);
    for (int ti = 0; ti < T; ti++) {
        int n;
        if (ti == 0) {
            // Edge case: single node
            n = 1;
        } else if (ti == 1) {
            // Edge case: two nodes
            n = 2;
        } else {
            // General case: between 3 and 12 nodes
            n = rnd.next(3, 12);
        }
        println(n);

        // Build a tree
        vector<array<int,3>> edges;
        if (n >= 2) {
            if (ti == 2) {
                // Chain: 0-1-2-...-(n-1)
                for (int i = 1; i < n; i++) {
                    int w = rnd.next(1, 100);
                    edges.push_back({i, i - 1, w});
                }
            } else if (ti == 3) {
                // Star centered at 0
                for (int i = 1; i < n; i++) {
                    int w = rnd.wnext(100, -1) + 1;  // weight skewed small
                    edges.push_back({i, 0, w});
                }
            } else {
                // Random tree by attaching i to a random previous node
                for (int i = 1; i < n; i++) {
                    int parent = rnd.next(0, i - 1);
                    int w;
                    int distChoice = rnd.next(0, 2);
                    if (distChoice == 0) {
                        w = rnd.next(1, 100);
                    } else if (distChoice == 1) {
                        w = rnd.wnext(100, -1) + 1;  // skew small
                    } else {
                        w = rnd.wnext(100, 1) + 1;   // skew large
                    }
                    // Randomize order of endpoints
                    if (rnd.next(0, 1) == 0)
                        edges.push_back({i, parent, w});
                    else
                        edges.push_back({parent, i, w});
                }
            }
            // Shuffle edge order for variability
            shuffle(edges.begin(), edges.end());

            // Output edges
            for (auto &e : edges) {
                println(e[0], e[1], e[2]);
            }
        }
    }

    // Terminate input
    println(0);
    return 0;
}
