#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10, "M");
    inf.readEoln();

    vector<int> visiblePrefix(n);
    int previousSolved = m + 1;
    for (int i = 0; i < n; ++i) {
        int solved = inf.readInt(0, m, "K_i");
        ensuref(solved <= previousSolved,
                "solved counts must be nonincreasing: K_%d=%d, K_%d=%d",
                i, previousSolved, i + 1, solved);
        previousSolved = solved;

        int knownSolved = 0;
        int unknown = 0;
        bool seenUnknown = false;
        int prefix = 0;
        for (int j = 0; j < m; ++j) {
            inf.readSpace();
            int result = inf.readInt(-1, 1, "result");

            if (result == -1) {
                seenUnknown = true;
                ++unknown;
            } else {
                ensuref(!seenUnknown,
                        "row %d has a visible result after an unknown result at problem %d",
                        i + 1, j + 1);
                ++prefix;
                if (result == 1) {
                    ++knownSolved;
                }
            }
        }
        inf.readEoln();

        ensuref(knownSolved <= solved && solved <= knownSolved + unknown,
                "K_%d=%d is inconsistent with %d known solved and %d unknown cells",
                i + 1, solved, knownSolved, unknown);
        visiblePrefix[i] = prefix;
    }

    for (int i = 1; i < n; ++i) {
        ensuref(visiblePrefix[i - 1] <= visiblePrefix[i],
                "visible prefix lengths must be nondecreasing: row %d has %d, row %d has %d",
                i, visiblePrefix[i - 1], i + 1, visiblePrefix[i]);
    }

    inf.readEof();
}
