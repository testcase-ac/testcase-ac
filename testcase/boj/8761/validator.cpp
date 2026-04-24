#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int Z = inf.readInt(1, 10, "Z");
    inf.readEoln();

    // Process each test case
    for (int t = 1; t <= Z; t++) {
        // Number of stations
        int N = inf.readInt(2, 1000000, "N");
        inf.readEoln();

        // Read station platform counts
        bool hasTwoPlatform = false;
        for (int i = 0; i < N; i++) {
            int s = inf.readInt(1, 2, "s_i");
            if (s == 2) {
                hasTwoPlatform = true;
            }
            if (i + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        // Ensure at least one station has two platforms
        ensuref(hasTwoPlatform,
                "Test case %d: at least one station must have two platforms", t);
    }

    // No extra data after all test cases
    inf.readEof();
    return 0;
}
