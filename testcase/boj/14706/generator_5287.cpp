#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checking
    int N = rnd.next(2, 10);

    // Hyper-parameter for M: sometimes small, sometimes large
    int t = rnd.next(-1, 1);  // bias: -1 small, 0 uniform, +1 large
    int M = 1 + rnd.wnext(N, t);  // yields in [1..N]

    // Generate unique lengths L_i
    vector<int> lengths(N);
    for (int i = 0; i < N; i++) lengths[i] = i + 1;
    shuffle(lengths.begin(), lengths.end());
    lengths.resize(M);

    // Build conditions (L_i, S_i)
    vector<pair<int,int>> cond;
    for (int L : lengths) {
        // Two modes for S: moderately tight or looser
        int S;
        if (rnd.next(0,1) == 0) {
            int lo = L;
            int hi = max(lo, L * 3);
            S = rnd.next(lo, hi);
        } else {
            int lo = L * 3;
            int hi = max(lo, L * 10);
            S = rnd.next(lo, hi);
        }
        cond.emplace_back(L, S);
    }

    // Shuffle conditions for random order
    shuffle(cond.begin(), cond.end());

    // Output
    println(N, M);
    for (auto &p : cond) {
        println(p.first, p.second);
    }
    return 0;
}
