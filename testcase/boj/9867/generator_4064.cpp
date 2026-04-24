#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(2, 10);
    int D = rnd.next(1, 10);

    // Hyper-parameter: choose an upper bound for initial capacities
    vector<int> possibleUm = {10, 50, 100, 1000, 100000};
    int M_upper = rnd.any(possibleUm);
    int M_lower = rnd.next(1, M_upper);

    // Generate initial milking capacities M[1..N]
    vector<int> M(N);
    for (int i = 0; i < N; i++) {
        M[i] = rnd.next(M_lower, M_upper);
    }

    // Hyper-parameter: probability to reuse the same machine index in updates
    double reuse_prob = rnd.next(0.0, 1.0);
    int last_i = rnd.next(1, N);

    // Generate D daily updates
    vector<pair<int,int>> updates;
    for (int d = 0; d < D; d++) {
        int idx;
        if (rnd.next() < reuse_prob) {
            idx = last_i;
        } else {
            idx = rnd.next(1, N);
        }
        last_i = idx;

        int new_m;
        if (rnd.next() < 0.5) {
            // small update in [1, M_upper]
            new_m = rnd.next(1, M_upper);
        } else {
            // possibly larger update up to 100000
            new_m = rnd.next(M_upper, 100000);
        }
        updates.emplace_back(idx, new_m);
    }

    // Output in the required format
    println(N, D);
    for (int i = 0; i < N; i++) {
        println(M[i]);
    }
    for (auto &u : updates) {
        println(u.first, u.second);
    }
    return 0;
}
