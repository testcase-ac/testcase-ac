#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Read each test case
    for (int tc = 1; tc <= T; tc++) {
        // n must satisfy 2 ≤ n ≤ 2×10^9
        long long n = inf.readLong(2LL, 2000000000LL, "n");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
