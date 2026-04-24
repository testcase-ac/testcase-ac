#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of days
    int N = rnd.next(2, 10);

    // Hyper-parameter: bias for K
    vector<int> biasOptions = {-1, 0, 1};
    int bias = rnd.any(biasOptions);
    // K in [1, N], biased small (bias<0), uniform (bias=0), or large (bias>0)
    int K = rnd.wnext(N, bias) + 1;

    // Hyper-parameter: temperature distribution type
    int distType = rnd.next(0, 2);
    int lo, hi;
    if (distType == 0) {
        // full range
        lo = -100;
        hi = 100;
    } else if (distType == 1) {
        // positive cluster
        lo = rnd.next(0, 50);
        hi = rnd.next(lo, 100);
    } else {
        // negative cluster
        hi = rnd.next(-50, 0);
        lo = rnd.next(-100, hi);
    }

    // Generate temperatures
    vector<int> temps(N);
    for (int i = 0; i < N; i++) {
        // occasionally force extremal values
        if (rnd.next() < 0.1) {
            vector<int> extremes = {lo, hi};
            temps[i] = rnd.any(extremes);
        } else {
            temps[i] = rnd.next(lo, hi);
        }
    }

    // Output
    println(N, K);
    println(temps);

    return 0;
}
