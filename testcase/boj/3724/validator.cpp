#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read M and N
        int M = inf.readInt(1, 20, "M");
        inf.readSpace();
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Read N rows, each with M 32-bit signed integers
        for (int i = 0; i < N; ++i) {
            // Use readInts to strictly enforce count and spacing
            vector<int> row = inf.readInts(M, -2147483648, 2147483647, "a_ij");
            inf.readEoln();
        }
    }

    inf.readEof();
}
