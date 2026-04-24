#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sequence length hyper-parameter
    int N = rnd.next(2, 10);
    // Balance of 1 and -1
    double p = rnd.next(); // probability of 1
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = (rnd.next() < p ? 1 : -1);
    }
    // Query count
    int maxQ = N * (N + 1) / 2;
    int M = rnd.next(1, min(20, maxQ));
    // Precompute length tiers
    int len1 = max(1, N / 3);
    int len2 = max(1, (2 * N) / 3);
    // Generate queries
    vector<pair<int,int>> qs;
    for (int qi = 0; qi < M; qi++) {
        int type = rnd.next(0, 3);
        int len;
        if (type == 0) {
            // small
            len = rnd.next(1, len1);
        } else if (type == 1) {
            // medium
            len = rnd.next(len1, len2);
        } else if (type == 2) {
            // large-ish
            len = rnd.next(len2, N);
        } else {
            // random length
            len = rnd.next(1, N);
        }
        // pick segment [i, j]
        int i = rnd.next(1, N - len + 1);
        int j = i + len - 1;
        qs.emplace_back(i, j);
    }
    // Optionally shuffle queries
    shuffle(qs.begin(), qs.end());
    // Output
    println(N);
    println(A);
    println(M);
    for (auto &q : qs) {
        println(q.first, q.second);
    }
    return 0;
}
