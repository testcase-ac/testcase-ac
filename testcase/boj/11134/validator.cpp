#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: 0 < T < 100
    int T = inf.readInt(1, 99, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // For each test case, read N and C on one line
        // 0 < N < 1e9, 0 < C < 5000
        long long N = inf.readLong(1LL, 999999999LL, "N");
        inf.readSpace();
        int C = inf.readInt(1, 4999, "C");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
