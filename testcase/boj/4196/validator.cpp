#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N (number of dominos) and M (number of relations)
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int M = inf.readInt(0, 100000, "M");
        inf.readEoln();

        // Read the M relations
        for (int i = 0; i < M; i++) {
            int x = inf.readInt(1, N, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, N, "y_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
