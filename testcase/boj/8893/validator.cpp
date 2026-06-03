#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound T; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalLength = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string s = inf.readToken("[LR]{4,100000}", "S");
        inf.readEoln();

        int leftTurns = 0;
        for (char c : s) {
            if (c == 'L') {
                ++leftTurns;
            }
        }
        int rightTurns = int(s.size()) - leftTurns;
        ensuref(leftTurns == rightTurns + 4,
                "case %d must have four more L turns than R turns, got L=%d R=%d",
                tc, leftTurns, rightTurns);

        totalLength += int(s.size());
        // CHECK: The statement bounds each string but not total input size.
        ensuref(totalLength <= 10000000LL,
                "total length of S strings exceeds local cap: %lld", totalLength);
    }

    inf.readEof();
}
