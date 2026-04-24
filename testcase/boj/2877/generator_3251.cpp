#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Three categories: small, medium, large
    int cat = rnd.next(0, 2);
    long long K;
    if (cat == 0) {
        // very small K for easy checks
        K = rnd.next(1, 10);
    } else if (cat == 1) {
        // medium K
        K = rnd.next(11, 10000);
    } else {
        // large K, skewed distribution to catch boundary issues
        vector<int> weights = {-3, -2, -1, 1, 2, 3};
        int t = rnd.any(weights);
        // rnd.wnext produces a value in [0, 1e9-1], then shift to [1,1e9]
        K = rnd.wnext(1000000000, t) + 1;
    }

    // Output a single test case
    println(K);
    return 0;
}
