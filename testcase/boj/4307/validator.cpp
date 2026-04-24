#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Process each test case
    for (int tc = 1; tc <= T; tc++) {
        // Read stick length l and number of ants n
        int l = inf.readInt(1, 1000000, "l");
        inf.readSpace();
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        // Read the positions of the n ants
        for (int i = 0; i < n; i++) {
            // Each position must be between 0 and l, inclusive
            inf.readInt(0, l, "position");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
