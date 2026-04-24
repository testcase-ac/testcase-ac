#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to use weighted sampling for K
    bool useWeighted = rnd.next(0, 1);
    int K;
    if (useWeighted) {
        // Choose a non-zero t for wnext to bias small or large K
        vector<int> ts = {-2, -1, 1, 2};
        int t = rnd.any(ts);
        // rnd.wnext(10, t) gives 0..9 biased; +1 shifts to 1..10
        K = rnd.wnext(10, t) + 1;
    } else {
        // Uniform K in [1,10]
        K = rnd.next(1, 10);
    }

    // Total sparks N = 1 + K + K^2
    long long N = 1LL + K + 1LL * K * K;
    println(N);

    return 0;
}
