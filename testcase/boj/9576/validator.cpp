#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 1000, "M");
        inf.readEoln();

        // For each student request [a_i, b_i]
        for (int i = 0; i < M; i++) {
            int a = inf.readInt(1, N, "a_i");
            inf.readSpace();
            // b must be at least a and at most N
            int b = inf.readInt(a, N, "b_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
