#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of villages
    int N = rnd.next(1, 10);

    // Hyper-parameter for maximum weight, skewed distribution
    int t = rnd.next(-1, 1);
    int Wmax = rnd.wnext(10000, t) + 1;

    // Generate weights for each village
    vector<int> weight(N);
    for (int i = 0; i < N; i++) {
        weight[i] = rnd.next(1, Wmax);
    }

    // Choose tree shape: 0=chain,1=star,2=random attachment
    int type = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (N >= 2) {
        if (type == 0) {
            // Chain in random order
            vector<int> order(N);
            iota(order.begin(), order.end(), 1);
            shuffle(order.begin(), order.end());
            for (int i = 0; i + 1 < N; i++) {
                edges.emplace_back(order[i], order[i+1]);
            }
        } else if (type == 1) {
            // Star centered at random node
            int center = rnd.next(1, N);
            for (int v = 1; v <= N; v++) {
                if (v != center) edges.emplace_back(center, v);
            }
        } else {
            // Random attachment tree
            for (int i = 2; i <= N; i++) {
                int p = rnd.next(1, i-1);
                edges.emplace_back(i, p);
            }
        }
    }

    // Permute labels to avoid bias
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    // Remap weights and edges according to permutation
    vector<int> weight2(N);
    for (int i = 0; i < N; i++) {
        weight2[perm[i]-1] = weight[i];
    }
    vector<pair<int,int>> edges2;
    for (auto &e : edges) {
        int u = perm[e.first-1];
        int v = perm[e.second-1];
        edges2.emplace_back(u, v);
    }
    shuffle(edges2.begin(), edges2.end());

    // Output
    println(N);
    println(weight2);
    for (auto &e : edges2) {
        println(e.first, e.second);
    }

    return 0;
}
