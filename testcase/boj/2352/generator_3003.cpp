#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose size
    int N = rnd.next(1, 10);
    // Base permutation 1..N
    vector<int> p(N);
    iota(p.begin(), p.end(), 1);
    // Choose pattern type for diversity
    int type = rnd.next(0, 4);
    if (type == 0) {
        // Fully random permutation
        shuffle(p.begin(), p.end());
    } else if (type == 1) {
        // Already sorted ascending: do nothing
    } else if (type == 2) {
        // Fully descending
        reverse(p.begin(), p.end());
    } else if (type == 3) {
        // Partial randomness: few swaps
        if (N >= 2) {
            int K = rnd.next(1, N/2);
            for (int i = 0; i < K; ++i) {
                int u = rnd.next(0, N-1);
                int v = rnd.next(0, N-1);
                swap(p[u], p[v]);
            }
        }
    } else {
        // Piecewise runs: ascending or descending segments
        if (N >= 2) {
            int R = rnd.next(2, min(N, 4));
            vector<int> cuts;
            cuts.push_back(0);
            for (int i = 0; i < R-1; ++i) {
                cuts.push_back(rnd.next(1, N-1));
            }
            cuts.push_back(N);
            sort(cuts.begin(), cuts.end());
            for (int i = 0; i < R; ++i) {
                int l = cuts[i];
                int r = cuts[i+1] - 1;
                if (rnd.next(0,1) == 0) {
                    reverse(p.begin()+l, p.begin()+r+1);
                }
            }
        }
    }
    // Output
    println(N);
    println(p);
    return 0;
}
