#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read N for this test case
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Read each pair (a_i, b_i)
        for (int i = 0; i < N; i++) {
            // a_i: time on oven 1, b_i: time on oven 2
            int a = inf.readInt(1, 100, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, 100, "b_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
