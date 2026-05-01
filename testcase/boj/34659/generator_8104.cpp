#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for variability
    int maxN = 12;
    vector<int> ts = {-2, -1, 1, 2};
    int t = rnd.any(ts);
    // Number of artists N in [1, maxN], skewed by weighted next
    int N = rnd.wnext(maxN, t) + 1;
    // Wall length D in [1, 30]
    int D = rnd.next(1, 30);

    // Decide whether colors repeat or are all distinct
    bool useRepeat = rnd.next(0, 1);
    vector<int> pool;
    if (useRepeat) {
        // Few distinct colors, repeated among artists
        int K = rnd.next(1, N);
        for (int i = 1; i <= K; ++i) pool.push_back(i);
    } else {
        // All artists have distinct colors
        pool.resize(N);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
    }

    // Generate segments [l_i, r_i] with color c_i
    vector<tuple<int,int,int>> segs;
    for (int i = 0; i < N; ++i) {
        // Segment length skewed small or large
        int tl = rnd.any(ts);
        int len = rnd.wnext(D, tl) + 1;  // in [1, D]
        if (len > D) len = D;
        int l = rnd.next(1, D - len + 1);
        int r = l + len - 1;
        int c = rnd.any(pool);
        segs.emplace_back(l, r, c);
    }

    // Output one test case
    println(D, N);
    for (auto &p : segs) {
        println(get<0>(p), get<1>(p), get<2>(p));
    }
    return 0;
}
