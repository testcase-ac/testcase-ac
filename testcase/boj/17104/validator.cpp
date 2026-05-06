#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read N and validate
    for (int i = 0; i < T; i++) {
        // Set the current test case context for better error messages
        setTestCase(i + 1);

        // N must satisfy: N is even, 2 < N <= 1e6
        // The smallest even N > 2 is 4.
        int N = inf.readInt(4, 1000000, "N");
        ensuref(N % 2 == 0,
                "Test case %d: N must be even, but found %d", 
                i + 1, N);

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
