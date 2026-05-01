#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rooms
    int N = rnd.next(2, 12);
    // Tree shape type: 0=path, 1=star, 2=random attach
    int type = rnd.next(0, 2);

    vector<pair<int,int>> edges;
    if (type == 0) {
        // Path tree with randomized node order
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        for (int i = 0; i + 1 < N; i++) {
            edges.emplace_back(nodes[i], nodes[i+1]);
        }
    } else if (type == 1) {
        // Star tree
        int center = rnd.next(1, N);
        for (int v = 1; v <= N; v++) {
            if (v == center) continue;
            edges.emplace_back(center, v);
        }
        shuffle(edges.begin(), edges.end());
    } else {
        // Random attachment tree
        for (int v = 2; v <= N; v++) {
            int u = rnd.next(1, v-1);
            edges.emplace_back(u, v);
        }
        shuffle(edges.begin(), edges.end());
    }

    // Decide max weight and bias for variability
    int weightMax = rnd.next(1, 10);
    int bias = rnd.next(-1, 1);

    vector<int> weights;
    for (int i = 0; i < N - 1; i++) {
        int w;
        if (bias < 0) {
            // bias towards small weights
            w = rnd.wnext(weightMax, -1) + 1;
        } else if (bias > 0) {
            // bias towards large weights
            w = rnd.wnext(weightMax, 1) + 1;
        } else {
            // uniform
            w = rnd.next(1, weightMax);
        }
        weights.push_back(w);
    }

    // Two distinct starting rooms for robots
    int a = rnd.next(1, N);
    int b;
    do {
        b = rnd.next(1, N);
    } while (b == a);

    // Output
    println(N, a, b);
    for (int i = 0; i < N - 1; i++) {
        println(edges[i].first, edges[i].second, weights[i]);
    }

    return 0;
}
