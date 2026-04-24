#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Number of nodes between 2 and 10
        int N = rnd.next(2, 10);

        // Generate a random topological order to guarantee a DAG
        vector<int> order(N);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());

        // All possible forward edges according to the order
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                cand.emplace_back(order[i], order[j]);
            }
        }

        // Hyper-parameter: edge density in [0,1)
        double density = rnd.next();

        // Select edges with probability = density
        vector<pair<int,int>> edges;
        for (auto &e : cand) {
            if (rnd.next() < density) {
                edges.push_back(e);
            }
        }
        // Ensure at least one edge (M >= 1)
        if (edges.empty()) {
            edges.push_back(rnd.any(cand));
        }

        // Hyper-parameter: add some duplicate edges to test multi-edge handling
        int edgeCount = int(edges.size());
        int dupCount = rnd.next(0, edgeCount);
        for (int i = 0; i < dupCount; ++i) {
            edges.push_back(rnd.any(edges));
        }

        // Shuffle final edge list
        shuffle(edges.begin(), edges.end());

        // Output this test case
        int M = int(edges.size());
        println(N, M);
        for (auto &e : edges) {
            println(e.first, e.second);
        }
    }

    return 0;
}
