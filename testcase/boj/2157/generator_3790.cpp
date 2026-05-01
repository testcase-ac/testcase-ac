#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of cities
    int N = rnd.next(2, 10);
    // Max number of visited cities
    int M = rnd.next(2, N);

    // Ensure at least one valid path of length <= M
    int maxPathLen = min(N, M);
    int pathLen = rnd.next(2, maxPathLen);

    // Build the nodes of the guaranteed path: start at 1, end at N
    vector<int> pathNodes;
    pathNodes.push_back(1);
    if (pathLen > 2) {
        // pick pathLen-2 distinct intermediate cities from [2..N-1]
        vector<int> pool;
        for (int x = 2; x <= N-1; ++x) pool.push_back(x);
        shuffle(pool.begin(), pool.end());
        pool.resize(pathLen - 2);
        sort(pool.begin(), pool.end());
        for (int x : pool) pathNodes.push_back(x);
    }
    pathNodes.push_back(N);

    // Hyper-parameter: choose cost upper bound
    vector<int> costCaps = {10, 100, 1000, 10000};
    int cap = rnd.any(costCaps);

    auto genCost = [&]() {
        // three modes: uniform, max-biased, min-biased
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            return rnd.next(1, cap);
        } else if (mode == 1) {
            return rnd.wnext(cap, 2) + 1;
        } else {
            return rnd.wnext(cap, -1) + 1;
        }
    };

    // Collect edges
    vector<tuple<int,int,int>> edges;
    // Path edges
    for (int i = 0; i + 1 < (int)pathNodes.size(); ++i) {
        int u = pathNodes[i];
        int v = pathNodes[i+1];
        int c = genCost();
        edges.emplace_back(u, v, c);
    }
    // Extra random edges
    int extra = rnd.next(0, N);
    for (int i = 0; i < extra; ++i) {
        int a, b;
        do {
            a = rnd.next(1, N);
            b = rnd.next(1, N);
        } while (a == b);
        int c = genCost();
        edges.emplace_back(a, b, c);
    }

    // Shuffle for randomness
    shuffle(edges.begin(), edges.end());

    // Output
    int K = edges.size();
    println(N, M, K);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }
    return 0;
}
