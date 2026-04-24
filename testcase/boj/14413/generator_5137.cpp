#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Number of distinct values to use
    int D = rnd.next(1, N);

    // Skew parameter for uneven distribution of values
    vector<int> skewOpts = {-2, -1, 0, 1, 2};
    int t = rnd.any(skewOpts);

    // Generate the array with values in [1..D]
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.wnext(D, t) + 1;
    }

    // Prepare queries with a mix of full, small, and random intervals
    vector<pair<int,int>> queries;
    for (int i = 0; i < Q; i++) {
        double p = rnd.next();
        int L, R;
        if (p < 0.2) {
            // Full interval
            L = 1;
            R = N;
        } else if (p < 0.6) {
            // Small interval of length up to 3
            int maxlen = min(3, N);
            int len = rnd.next(1, maxlen);
            L = rnd.next(1, N - len + 1);
            R = L + len - 1;
        } else {
            // Uniform random interval
            L = rnd.next(1, N);
            R = rnd.next(L, N);
        }
        queries.emplace_back(L, R);
    }

    // Shuffle query order
    shuffle(queries.begin(), queries.end());

    // Output
    println(N, Q);
    println(a);
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}
