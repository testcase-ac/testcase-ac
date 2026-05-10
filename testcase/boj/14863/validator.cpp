#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // For each of N segments, read walking time, walking donation,
    // biking time, biking donation, and accumulate minimal time.
    long long sumMinTime = 0;
    for (int i = 1; i <= N; i++) {
        int w_t = inf.readInt(1, 10000, "walk_time");
        inf.readSpace();
        int w_d = inf.readInt(1, 1000000, "walk_donation");
        inf.readSpace();
        int b_t = inf.readInt(1, 10000, "bike_time");
        inf.readSpace();
        int b_d = inf.readInt(1, 1000000, "bike_donation");
        inf.readEoln();

        sumMinTime += min(w_t, b_t);
    }

    // Check the implied global constraint: it's always possible to finish within K minutes.
    ensuref(sumMinTime <= K,
            "Minimal possible total time %lld exceeds K=%d", sumMinTime, K);

    inf.readEof();
    return 0;
}
