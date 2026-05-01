#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose N in small, medium, or slightly larger range
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) N = rnd.next(2, 5);
    else if (mode == 1) N = rnd.next(6, 20);
    else N = rnd.next(21, 30);
    // Probability of negative values in random blocks
    double negProb = rnd.next(0.0, 1.0);
    // Partition into blocks to create structured patterns
    int B = rnd.next(1, min(N, 5));
    vector<int> sz(B, 1);
    int rem = N - B;
    for (int i = 0; i < rem; ++i) {
        sz[rnd.next(0, B-1)]++;
    }
    vector<long long> P;
    P.reserve(N);
    for (int b = 0; b < B; ++b) {
        int type = rnd.next(0, 2); // 0=increasing,1=decreasing,2=random
        long long lastVal = rnd.next(-1000, 1000);
        for (int i = 0; i < sz[b]; ++i) {
            long long v;
            if (type == 0) {
                v = lastVal + rnd.next(0, 20);
                if (v > 1000000000LL) v = 1000000000LL;
                lastVal = v;
            } else if (type == 1) {
                v = lastVal - rnd.next(0, 20);
                if (v < -1000000000LL) v = -1000000000LL;
                lastVal = v;
            } else {
                // fully random with negatives, positives, zeros, spikes
                if (rnd.next() < 0.05) {
                    v = 0;
                } else if (rnd.next() < negProb) {
                    if (rnd.next() < 0.1) v = rnd.next(-1000000000, -100000);
                    else v = rnd.next(-100, -1);
                } else {
                    if (rnd.next() < 0.1) v = rnd.next(100000, 1000000000);
                    else v = rnd.next(1, 200);
                }
            }
            P.push_back(v);
        }
    }
    // Output
    println(N);
    println(P);
    return 0;
}
