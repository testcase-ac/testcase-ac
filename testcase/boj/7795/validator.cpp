#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read N and M
        int N = inf.readInt(1, 20000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 20000, "M");
        inf.readEoln();

        // Read sizes of A
        inf.readInts(N, 1, 1000000000, "A_i");
        inf.readEoln();

        // Read sizes of B
        inf.readInts(M, 1, 1000000000, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
