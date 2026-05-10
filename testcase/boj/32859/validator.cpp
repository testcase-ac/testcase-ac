#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 2000;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2 * N, "M");
    inf.readEoln();

    int S = inf.readInt(1, N, "S");
    inf.readEoln();

    // Track per-member constraints
    vector<bool> hasForm(N + 1, false);
    vector<bool> hasDeposit(N + 1, false);

    // For global property: "입금한 시점 이후 다른 S명이 폼을 제출한 후에도
    // 폼을 제출하지 않은 회원은 ... 존재" is definition of answer,
    // not a promised property that always/never happens, so no extra check.

    // We will simulate events to later be able to check any promised
    // constraints if necessary. For now, just enforce per-member rules.
    vector<pair<int,int>> events;
    events.reserve(M);

    for (int k = 0; k < M; ++k) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int t = inf.readInt(0, 1, "t");
        inf.readEoln();

        // No member submits form more than once
        if (t == 0) {
            ensuref(!hasForm[i],
                    "Member %d submits form more than once (event index %d)", i, k + 1);
            hasForm[i] = true;
        }
        // No member deposits more than once
        else { // t == 1
            ensuref(!hasDeposit[i],
                    "Member %d deposits more than once (event index %d)", i, k + 1);
            hasDeposit[i] = true;
        }

        events.push_back({i, t});
    }

    // No extra whitespace after the last line
    inf.readEof();
}
