#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T and N
    int T = inf.readInt(1, 5000, "T");
    inf.readSpace();
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Read durations d[i]
    vector<int> d = inf.readInts(N, 1, T, "d");
    inf.readEoln();

    // Global constraint: total sum of durations must be <= 2*T
    long long total = 0;
    for (int i = 0; i < N; i++) {
        total += d[i];
    }
    ensuref(total <= 2LL * T,
            "Sum of all durations (%lld) exceeds 2*T (%lld)", 
            total, 2LL * T);

    // Each break must fit on one machine: d[i] <= T, already checked by readInts

    // Check that it's possible to schedule these N non-preemptive jobs
    // of lengths d[i] on 2 machines within makespan T.
    // That is, there exists a subset S with sum S in [total-T, T].
    int lower = (int)max(0LL, total - (long long)T);
    int upper = T;
    // dp[s] = can we get sum s
    vector<char> dp(T + 1, 0);
    dp[0] = 1;
    for (int x : d) {
        // iterate backwards
        for (int s = T; s >= x; s--) {
            if (dp[s - x]) dp[s] = 1;
        }
    }
    bool feasible = false;
    for (int s = lower; s <= upper; s++) {
        if (dp[s]) {
            feasible = true;
            break;
        }
    }
    ensuref(feasible,
            "Cannot schedule durations within T=%d on 2 machines (no valid partition)", T);

    inf.readEof();
    return 0;
}
