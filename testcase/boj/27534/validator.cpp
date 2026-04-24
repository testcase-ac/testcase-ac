#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    long long sum_n = 0;
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();

        // Read binary string
        string s = inf.readLine("[01]+", "s");
        // Check length matches n
        ensuref((int)s.size() == n,
                "In test case %d, length of binary string is %d but expected %d",
                tc, (int)s.size(), n);

        // Accumulate and check sum of n
        sum_n += n;
        ensuref(sum_n <= 1000000LL,
                "Sum of n over all test cases exceeds 1e6 (got %lld)", sum_n);
    }

    inf.readEof();
    return 0;
}
