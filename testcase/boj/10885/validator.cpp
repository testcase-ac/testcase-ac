#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Length of the sequence
        int N = inf.readInt(2, 100000, "N");
        inf.readEoln();

        totalN += N;
        ensuref(totalN <= 300000LL,
                "Sum of N over all test cases exceeds 300000: %lld", totalN);

        // Sequence elements
        vector<int> a = inf.readInts(N, -2, 2, "a_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
