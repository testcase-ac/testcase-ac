#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Size of the sequence, must be odd
        int M = inf.readInt(1, 9999, "M");
        ensuref(M % 2 == 1, "M must be odd, but got %d", M);
        inf.readEoln();

        // The sequence elements: divided into lines of 10 elements each
        int full_lines = M / 10;
        int rem = M % 10;
        int total_lines = full_lines + (rem > 0 ? 1 : 0);
        for (int i = 0; i < total_lines; i++) {
            int cnt = (i < full_lines ? 10 : (rem > 0 ? rem : 10));
            inf.readInts(cnt, -2147483648, 2147483647, "a");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
