#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of bottles
    int N = rnd.next(1, 10);

    // Hyper-parameter: drawer count relative to N
    double p = rnd.next();
    int low, high;
    if (p < 0.3) {
        low = 2;
        high = max(2, N);
    } else if (p < 0.6) {
        low = N + 1;
        high = 2 * N;
    } else {
        low = 2 * N + 1;
        high = 3 * N;
    }
    int L = rnd.next(low, high);

    // Hyper-parameter: whether to focus pairs in a small cluster
    bool useCluster = rnd.next(0, 1) == 1;
    int clusterSize = 0;
    if (useCluster && L >= 2) {
        clusterSize = rnd.next(2, min(L, 5));
    }

    // Generate pairs (A_i, B_i)
    vector<pair<int,int>> ab;
    for (int i = 0; i < N; i++) {
        int A, B;
        if (clusterSize > 0 && rnd.next() < 0.7) {
            // biased to small cluster
            A = rnd.next(1, clusterSize);
            do {
                B = rnd.next(1, clusterSize);
            } while (B == A);
        } else {
            // uniform over full range
            A = rnd.next(1, L);
            do {
                B = rnd.next(1, L);
            } while (B == A);
        }
        ab.emplace_back(A, B);
    }

    // Optionally shuffle the order of operations to add diversity
    if (rnd.next(0,1)) {
        shuffle(ab.begin(), ab.end());
    }

    // Output
    println(N, L);
    for (auto &pr : ab) {
        println(pr.first, pr.second);
    }
    return 0;
}
