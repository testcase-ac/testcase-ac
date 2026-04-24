#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: array size between 2 and 10
    int N = rnd.next(2, 10);

    // Hyper-parameter: number of calls between 1 and min(20, 5*N)
    int K = rnd.next(1, min(20, 5 * N));

    // Generate jumps X_i with bias: use weighted next to favor small or large jumps
    // t in [-2,2]: negative t favors small values, positive t favors large
    int t = rnd.next(-2, 2);
    vector<int> X(K);
    for (int i = 0; i < K; i++) {
        // rnd.wnext(N-1, t) gives [0, N-2], add 1 => [1, N-1]
        X[i] = rnd.wnext(N - 1, t) + 1;
    }

    // Hyper-parameter: sometimes sort the jumps, sometimes shuffle
    if (rnd.next(0, 1) == 0) {
        sort(X.begin(), X.end());
    } else {
        shuffle(X.begin(), X.end());
    }

    // Hyper-parameter: number of queries between 1 and 10
    int Q = rnd.next(1, 10);
    vector<pair<int,int>> queries;
    queries.reserve(Q);
    for (int i = 0; i < Q; i++) {
        double p = rnd.next();
        int L, R;
        if (p < 0.2) {
            // full range
            L = 0; R = N - 1;
        } else if (p < 0.4) {
            // single point
            L = rnd.next(0, N - 1);
            R = L;
        } else {
            // random range
            L = rnd.next(0, N - 2);
            R = rnd.next(L + 1, N - 1);
        }
        queries.emplace_back(L, R);
    }

    // Output
    println(N, K);
    println(X);
    println(Q);
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}
