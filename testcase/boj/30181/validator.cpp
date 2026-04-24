#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries Q
    int Q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    // Track which students (by enter index) are currently in the lab
    // We use 1-based indexing: inLab[1] corresponds to the first entrant.
    vector<char> inLab(1, 0);
    int enterCount = 0;  // Total number of type-1 queries seen

    for (int qi = 1; qi <= Q; qi++) {
        // Read query type
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        if (t == 1) {
            // Entry event: read x
            int x = inf.readInt(1, 1000000, "x");
            // A new student enters
            enterCount++;
            inLab.push_back(1);
        }
        else if (t == 2) {
            // Exit event: read k
            // k must refer to an already-entered student
            int k = inf.readInt(1, enterCount, "k");
            // That student must currently be in the lab
            ensuref(inLab[k],
                    "Query %d: student %d is not currently in the lab but is asked to exit",
                    qi, k);
            inLab[k] = 0;
        }
        else { // t == 3
            // Event: read s
            int s = inf.readInt(1, 1000000000, "s");
            (void)s; // no state change needed
        }
        inf.readEoln();
    }

    // There must be at least one type-1 query overall
    ensuref(enterCount >= 1,
            "There must be at least one type-1 query, but none found");

    inf.readEof();
    return 0;
}
