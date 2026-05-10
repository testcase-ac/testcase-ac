#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 300, "t");
    inf.readEoln();

    long long sum_n = 0;
    for (int tc = 1; tc <= t; tc++) {
        setTestCase(tc);
        // Read n for this test case
        int n = inf.readInt(1, 2000, "n");
        inf.readEoln();

        // Read string S consisting of 'A' and 'B'
        string s = inf.readToken("[AB]+", "S");
        inf.readEoln();

        // Check that the length matches n
        ensuref((int)s.size() == n,
                "In test case %d: length of S is %d but n is %d",
                tc, (int)s.size(), n);

        sum_n += n;
    }

    // Check global constraint on sum of n
    ensuref(sum_n <= 2000,
            "Sum of n over all test cases is %lld but must not exceed 2000",
            sum_n);

    inf.readEof();
    return 0;
}
