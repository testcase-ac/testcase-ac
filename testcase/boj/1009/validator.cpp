#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        setTestCase(tc + 1);

        // a: base, 1 <= a < 100
        int a = inf.readInt(1, 99, "a_i");
        inf.readSpace();
        // b: exponent, 1 <= b < 1,000,000
        int b = inf.readInt(1, 999999, "b_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
