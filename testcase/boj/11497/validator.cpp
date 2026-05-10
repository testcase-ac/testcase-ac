#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(5, 10000, "N");
        inf.readEoln();

        // Read the heights
        inf.readInts(N, 1, 100000, "L_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
