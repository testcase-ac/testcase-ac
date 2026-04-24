#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read n
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        // Read the sequence of length n
        // Values are between 1 and 1e12 inclusive
        vector<long long> a = inf.readLongs(n, 1LL, 1000000000000LL, "a_i");
        inf.readEoln();
    }

    // No extra characters after all test cases
    inf.readEof();
    return 0;
}
