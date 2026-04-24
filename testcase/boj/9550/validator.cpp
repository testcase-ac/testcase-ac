#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and K
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int K = inf.readInt(1, 100, "K");
        inf.readEoln();

        // Read candy counts
        inf.readInts(N, 1, 100, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
