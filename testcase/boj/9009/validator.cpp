#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: not specified in statement, assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Each test case has one integer n, 1 ≤ n ≤ 1e9
        long long n = inf.readLong(1LL, 1000000000LL, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
