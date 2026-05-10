#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, X
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int X = inf.readInt(2, 200, "X");
    inf.readEoln();

    // Read N buses, each with S and T
    int feasibleCount = 0;
    int bestS = -1;

    for (int i = 0; i < N; i++) {
        int S = inf.readInt(1, 100, "S");
        inf.readSpace();
        int T = inf.readInt(1, 100, "T");
        inf.readEoln();

        // For validator: check the implied global property:
        // "If it is possible to arrive within X minutes" -> either no such bus
        // or the answer is at most X (because S >= 1 and T >= 1, but we just
        // need to verify that the actual optimal bus exists).
        // We simulate choosing the latest-starting feasible bus.
        if (S + T <= X) {
            feasibleCount++;
            if (S > bestS) bestS = S;
        }
    }

    // No explicit guarantee from the statement that a feasible bus always exists,
    // only that it may or may not exist. So we do NOT enforce feasibility here.
    // However, we can sanity-check that if there is a feasible bus,
    // the "answer" S does not exceed X (this must always hold since S+T<=X and T>=1).
    if (feasibleCount > 0) {
        ensuref(bestS >= 1 && bestS <= X,
                "Computed best S = %d out of range [1, X=%d]", bestS, X);
    }

    inf.readEof();
}
