#include "testlib.h"
#include <vector>
#include <tuple>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 4);
    for (int ti = 0; ti < T; ti++) {
        if (ti == 0) {
            // Include a trivial case with one point
            println(1, 0);
            printf("\n");
            continue;
        }
        // Generate P
        bool small = rnd.next(0, 1);
        int P = small ? rnd.next(2, 5) : rnd.next(6, 10);
        vector<int> nodes(P);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());

        // Weight distribution hyper-parameter
        vector<int> weightTypes = {-2, -1, 0, 1, 2};
        int wType = rnd.any(weightTypes);

        vector<tuple<int,int,int>> routes;
        // Ensure connectivity via random spanning tree
        for (int i = 1; i < P; i++) {
            int u = nodes[i];
            int v = nodes[rnd.next(0, i-1)];
            int w = rnd.wnext(100, wType) + 1;
            routes.emplace_back(u, v, w);
        }
        // Add extra routes (possibly parallel edges)
        int extras = rnd.next(0, P);
        for (int i = 0; i < extras; i++) {
            int u = rnd.next(1, P), v = rnd.next(1, P);
            while (v == u) v = rnd.next(1, P);
            int w = rnd.wnext(100, wType) + 1;
            routes.emplace_back(u, v, w);
        }
        // Shuffle and randomize direction
        shuffle(routes.begin(), routes.end());
        println(P, (int)routes.size());
        for (auto &t : routes) {
            int u, v, w;
            tie(u, v, w) = t;
            if (rnd.next(0, 1)) swap(u, v);
            println(u, v, w);
        }
        // Blank line between datasets
        printf("\n");
    }
    // Termination
    println(0);
    return 0;
}
