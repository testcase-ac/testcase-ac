#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, D
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int D = inf.readInt(1, 300000, "D");
    inf.readEoln();

    // Second line: h_i
    vector<int> h(N);
    long long sumH = 0;
    for (int i = 0; i < N; ++i) {
        h[i] = inf.readInt(1, 300000, "h_i");
        sumH += h[i];
        if (i + 1 < N) inf.readSpace();
        else inf.readEoln();
    }

    // Global property: process is well-defined and must match problem description.
    // We validate:
    // - On each of D days, if there is any building with positive height,
    //   we decrease by 1 the height of all buildings that currently have the maximum height.
    // - If all buildings are zero, no further changes.
    //
    // We don't know the official answer output (this is just the validator),
    // but we must ensure that the total number of laser shots fits in 64-bit signed
    // as the statement warns 32-bit may overflow. We'll verify that explicitly.

    // Simulate in a way sufficient to compute total laser shots and check for overflow.
    // Because heights and D are up to 3e5, a naive day-by-day simulation could be costly,
    // but here it's only for validation on test data (same limits as solutions),
    // so we should still keep it efficient enough.
    //
    // We just need to compute total number of decrements during at most D iterations,
    // but direct simulation of max each day O(ND) is too big.
    //
    // However, for validation we only need to ensure that the number of laser shots
    // is within 64-bit and that process is consistent with constraints.
    // Note: sumH <= N * 300000 = 9e10, which is safely < 2^63,
    // and the total number of decrements is at most sumH,
    // because each building's height decreases from h_i to 0 at most.
    //
    // So we don't actually need to simulate; we can just assert this bound.
    // But to respect the guideline "if the problem says answer may exceed 32-bit,
    // validate by computing and checking bounds", we compute the exact total number
    // of shots that *could* ever be fired and ensure it's within signed 64-bit.
    //
    // The total number of shots is at most sum(h_i), because each shot reduces
    // some building's height by 1, and heights never go below 0.
    // Hence totalShots <= sumH. sumH fits into signed 64-bit as argued above.
    // We still check this explicitly.

    long long maxPossibleShots = sumH; // upper bound on total laser firings
    // Check that this fits in signed 64-bit (it does by construction, but we assert).
    // 2^63 - 1 = 9223372036854775807
    ensuref(maxPossibleShots >= 0 && maxPossibleShots <= 9223372036854775807LL,
            "Total possible number of laser shots (%lld) must fit in signed 64-bit",
            maxPossibleShots);

    // There are no more global structural properties (no graphs, polygons, etc.)
    // Process is always well-defined given constraints.

    inf.readEof();
}
