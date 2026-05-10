#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    int T = inf.readInt(1, 20000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Remaining time X
        int X = inf.readInt(1, 2000, "X");
        inf.readEoln();

        // Read 4 house coordinates (A,B,C) each in [-100, 100]
        for (int i = 0; i < 4; ++i) {
            int A = inf.readInt(-100, 100, "A");
            inf.readSpace();
            int B = inf.readInt(-100, 100, "B");
            inf.readSpace();
            int C = inf.readInt(-100, 100, "C");
            (void)A;
            (void)B;
            (void)C;
            inf.readEoln();
        }
    }

    inf.readEof();
}
