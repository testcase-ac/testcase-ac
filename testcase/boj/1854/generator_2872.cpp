#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cities and k-th path
    int n = rnd.next(1, 10);
    int k = rnd.next(1, 10);

    // Build all possible directed edges (excluding self loops)
    vector<pair<int,int>> cand;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) cand.emplace_back(i, j);
        }
    }
    // Hyper-parameter: edge density
    double density = rnd.next(0.0, 1.0);
    shuffle(cand.begin(), cand.end());

    // Select edges with given probability
    vector<pair<int,int>> edges;
    for (auto &e : cand) {
        if (rnd.next() < density) {
            edges.push_back(e);
        }
    }
    int m = edges.size();

    // Hyper-parameter: cost distribution bias
    int maxC = rnd.next(1, 20);
    int bias = rnd.next(-2, 2);

    // Output
    println(n, m, k);
    for (auto &e : edges) {
        // costs from 1 to maxC, skewed by bias
        int c = rnd.wnext(maxC, bias) + 1;
        println(e.first, e.second, c);
    }
    return 0;
}
