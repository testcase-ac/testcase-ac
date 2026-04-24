#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Number of days
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // For each day, read profits for A, B, C
        for (int i = 0; i < N; i++) {
            // Three integers: A, B, C profits in [-1e6, 1e6]
            inf.readInts(3, -1000000, 1000000, "profit");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
