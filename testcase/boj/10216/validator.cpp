#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Mark this test case for error reporting
        setTestCase(tc + 1);

        // Number of enemy camps N
        int N = inf.readInt(1, 3000, "N");
        inf.readEoln();

        // Each camp: x, y, R
        for (int i = 0; i < N; i++) {
            int x = inf.readInt(0, 5000, "x_i");
            inf.readSpace();
            int y = inf.readInt(0, 5000, "y_i");
            inf.readSpace();
            int R = inf.readInt(0, 5000, "R_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
