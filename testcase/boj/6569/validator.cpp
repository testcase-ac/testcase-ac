#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect multiple test cases of "h w" pairs, ending with "0 0"
    // Constraints: 1 ≤ h, w ≤ 11 for actual cases; sentinel 0 0 only at end.
    // Number of test cases (excluding sentinel) ≤ 100000.
    int lineNo = 0;
    int caseNo = 0;
    while (true) {
        lineNo++;
        // Read h and w in [0,11]; we'll enforce h,w >=1 for real cases
        int h = inf.readInt(0, 11, "h");
        inf.readSpace();
        int w = inf.readInt(0, 11, "w");
        inf.readEoln();

        // Sentinel check
        if (h == 0 && w == 0) {
            break;
        }
        // For real cases, dimensions must be at least 1
        ensuref(h >= 1,
                "At line %d: h must be between 1 and 11, but got %d",
                lineNo, h);
        ensuref(w >= 1,
                "At line %d: w must be between 1 and 11, but got %d",
                lineNo, w);

        caseNo++;
        ensuref(caseNo <= 100000,
                "Number of test cases exceeds 100000: %d",
                caseNo);
    }

    inf.readEof();
    return 0;
}
