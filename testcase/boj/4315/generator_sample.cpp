#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, 14);

        vector<vector<int>> children(n + 1);
        for (int v = 2; v <= n; ++v) {
            int parent;
            if (mode == 0) {
                parent = v - 1;
            } else if (mode == 1) {
                parent = 1;
            } else if (mode == 2) {
                parent = v / 2;
            } else {
                parent = rnd.next(1, v - 1);
            }
            children[parent].push_back(v);
        }

        vector<int> marbles(n + 1, 0);
        int marbleMode = rnd.next(0, 3);
        if (marbleMode == 0) {
            marbles[rnd.next(1, n)] = n;
        } else if (marbleMode == 1) {
            for (int v = 1; v <= n; ++v) marbles[v] = 1;
            int moves = rnd.next(0, n);
            for (int i = 0; i < moves; ++i) {
                vector<int> donors;
                for (int v = 1; v <= n; ++v) {
                    if (marbles[v] > 0) donors.push_back(v);
                }
                int from = rnd.any(donors);
                int to = rnd.next(1, n);
                --marbles[from];
                ++marbles[to];
            }
        } else {
            for (int i = 0; i < n; ++i) {
                ++marbles[rnd.next(1, n)];
            }
        }

        vector<int> order;
        for (int v = 1; v <= n; ++v) {
            shuffle(children[v].begin(), children[v].end());
            order.push_back(v);
        }
        shuffle(order.begin(), order.end());

        println(n);
        for (int v : order) {
            printf("%d %d %d", v, marbles[v], int(children[v].size()));
            for (int child : children[v]) printf(" %d", child);
            printf("\n");
        }
    }

    println(0);
    return 0;
}
