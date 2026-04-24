#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 400000, "M");
    inf.readEoln();

    // Track which students are still on the bus
    vector<char> present(N+1, 1);

    int cntType2 = 0;
    for (int i = 0; i < M; i++) {
        // Each query
        int t = inf.readInt(1, 2, "type");
        inf.readSpace();
        int x = inf.readInt(1, N, "x");
        inf.readEoln();

        if (t == 1) {
            // Removal: student x must be present
            ensuref(present[x],
                    "Operation %d: student %d is not on the bus (double removal?)",
                    i+1, x);
            present[x] = 0;
        } else {
            // Query
            cntType2++;
        }
    }

    // There must be at least one type-2 query
    ensuref(cntType2 > 0, "Input must contain at least one type-2 query");

    inf.readEof();
    return 0;
}
