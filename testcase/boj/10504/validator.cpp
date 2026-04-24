#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: assumed up to 100,000 if not specified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read N
    for (int i = 0; i < T; i++) {
        // N is between 1 and 10^9 inclusive
        long long N = inf.readLong(1LL, 1000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
