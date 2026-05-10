#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Daily delivered feed N
        long long N = inf.readLong(1LL, 500000000LL, "N");
        inf.readEoln();

        // Initial amounts for pigs 1 through 6
        vector<int> a = inf.readInts(6, 1, 100, "a");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
