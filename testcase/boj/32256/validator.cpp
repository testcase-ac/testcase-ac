#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 <= T <= 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: one integer N: 1 <= N <= 1e18
    for (int i = 0; i < T; i++) {
        long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
