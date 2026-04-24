#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable cases
    int N = rnd.next(2, 10);
    int K = rnd.next(1, min(N, 5));
    int M = rnd.next(1, 10);

    vector<vector<int>> tubes;
    // Decide whether to build a guaranteed chain path
    bool useChain = (K >= 2 && N >= 3 && rnd.next() < 0.5);
    if (useChain) {
        // Number of tubes in the chain path
        int maxT = min(min(M, 4), N - 1);
        int T = rnd.next(1, maxT);
        // Choose T-1 distinct intermediate stations from [2..N-1]
        vector<int> mids;
        if (T >= 2) {
            vector<int> pool;
            for (int x = 2; x <= N - 1; ++x) pool.push_back(x);
            shuffle(pool.begin(), pool.end());
            mids.assign(pool.begin(), pool.begin() + (T - 1));
        }
        // Build the full path: 1 -> mids... -> N
        vector<int> path;
        path.push_back(1);
        for (int x : mids) path.push_back(x);
        path.push_back(N);
        // Create hyper-tubes along the path
        for (int i = 1; i < (int)path.size(); ++i) {
            int u = path[i - 1], v = path[i];
            vector<int> pool;
            for (int x = 1; x <= N; ++x)
                if (x != u && x != v)
                    pool.push_back(x);
            shuffle(pool.begin(), pool.end());
            vector<int> tube;
            tube.push_back(u);
            tube.push_back(v);
            for (int j = 0; j < K - 2; ++j)
                tube.push_back(pool[j]);
            shuffle(tube.begin(), tube.end());
            tubes.push_back(tube);
        }
        // Fill remaining tubes randomly
        while ((int)tubes.size() < M) {
            vector<int> pool(N);
            iota(pool.begin(), pool.end(), 1);
            shuffle(pool.begin(), pool.end());
            vector<int> tube;
            for (int j = 0; j < K; ++j)
                tube.push_back(pool[j]);
            shuffle(tube.begin(), tube.end());
            tubes.push_back(tube);
        }
    } else {
        // Fully random tubes
        for (int i = 0; i < M; ++i) {
            vector<int> pool(N);
            iota(pool.begin(), pool.end(), 1);
            shuffle(pool.begin(), pool.end());
            vector<int> tube;
            for (int j = 0; j < K; ++j)
                tube.push_back(pool[j]);
            shuffle(tube.begin(), tube.end());
            tubes.push_back(tube);
        }
    }

    // Output the generated test case
    println(N, K, M);
    for (auto &tube : tubes)
        println(tube);

    return 0;
}
