#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseNo = 0;
    while (true) {
        // Read one test case: L, P, V
        int L = inf.readInt(0, INT_MAX, "L");
        inf.readSpace();
        int P = inf.readInt(0, INT_MAX, "P");
        inf.readSpace();
        int V = inf.readInt(0, INT_MAX, "V");
        inf.readEoln();

        // Terminator
        if (L == 0 && P == 0 && V == 0) {
            break;
        }

        // Count cases and enforce limit
        caseNo++;
        ensuref(caseNo <= 100000, "Number of test cases exceeds 100000: %d", caseNo);

        // Enforce 1 < L < P < V
        ensuref(L > 1, "L must be > 1 at case %d: got L=%d", caseNo, L);
        ensuref(P > L, "P must be > L at case %d: L=%d, P=%d", caseNo, L, P);
        ensuref(V > P, "V must be > P at case %d: P=%d, V=%d", caseNo, P, V);
    }

    inf.readEof();
    return 0;
}
