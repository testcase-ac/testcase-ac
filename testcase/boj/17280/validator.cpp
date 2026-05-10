#include "testlib.h"
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N (number of passengers) and M (number of drivers)
        int N = inf.readInt(1, 1000000000, "N");
        inf.readSpace();
        int M = inf.readInt(0, 1000000000, "M");
        inf.readEoln();

        // Read the destinations of the N passengers
        inf.readInts(N, 1, 1000000000, "x_i");
        inf.readEoln();

        // Read the intervals [y_j, z_j] for each of the M drivers
        for (int j = 0; j < M; ++j) {
            int y = inf.readInt(1, 1000000000, "y_j");
            inf.readSpace();
            int z = inf.readInt(1, 1000000000, "z_j");
            inf.readEoln();
            ensuref(y <= z,
                    "Driver %d: y_j (%d) > z_j (%d)", 
                    j + 1, y, z);
        }
    }

    inf.readEof();
    return 0;
}
