#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T (1 ≤ T ≤ 10)
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // For each test case, read M and N
        // 1 ≤ M ≤ 4, 1 ≤ N ≤ 10^9
        int M = inf.readInt(1, 4, "M");
        inf.readSpace();
        long long N = inf.readLong(1LL, 1000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
