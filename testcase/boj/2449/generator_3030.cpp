#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int N = rnd.next(1, 10);
    int K = rnd.next(1, min(20, N));

    // Number of consecutive segments
    int S = (K == 1 ? 1 : rnd.next(1, N));

    // Assign segment lengths summing to N
    vector<int> len(S, 1);
    int rem = N - S;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, S - 1);
        len[idx]++;
    }

    // Assign colors to segments, ensuring adjacent segments differ
    vector<int> col(S);
    col[0] = rnd.next(1, K);
    for (int i = 1; i < S; i++) {
        // pick from 1..K except col[i-1]
        int x = rnd.next(1, K - 1);
        col[i] = (x >= col[i-1] ? x + 1 : x);
    }

    // Build the full sequence
    vector<int> res;
    res.reserve(N);
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < len[i]; j++) {
            res.push_back(col[i]);
        }
    }

    // Random rotation to diversify edge cases
    if (N > 1 && rnd.next(0, 1)) {
        int r = rnd.next(0, N - 1);
        rotate(res.begin(), res.begin() + r, res.end());
    }

    // Randomly permute color labels
    if (K > 1 && rnd.next(0, 1)) {
        vector<int> perm(K);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < N; i++) {
            res[i] = perm[res[i] - 1];
        }
    }

    // Output
    println(N, K);
    println(res);

    return 0;
}
