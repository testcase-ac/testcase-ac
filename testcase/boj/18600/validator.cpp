#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Number of presents
        int n = inf.readInt(1, 10000, "n");
        sumN += n;
        inf.readEoln();

        // Probabilities P_i: each must be in [0,1] with exactly six decimal places
        // Accepted format: "0.xxxxxx" or "1.000000"
        const char* probRegex = "0\\.[0-9]{6}|1\\.000000";
        for (int i = 0; i < n; i++) {
            inf.readToken(probRegex, "P_i");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Check global constraint on sum of n
    ensuref(sumN <= 500000,
            "Sum of n over all test cases must not exceed 500000, but got %lld",
            sumN);

    inf.readEof();
    return 0;
}
