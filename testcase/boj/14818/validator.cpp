#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, C, M
        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        int C = inf.readInt(2, 1000, "C");
        inf.readSpace();
        int M = inf.readInt(1, 1000, "M");
        inf.readEoln();

        // Read the M tickets
        for (int i = 0; i < M; i++) {
            int P = inf.readInt(1, N, "P_i");
            inf.readSpace();
            int B = inf.readInt(1, C, "B_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
