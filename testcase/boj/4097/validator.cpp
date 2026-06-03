#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalDays = 0;
    int testCase = 0;
    while (true) {
        int n = inf.readInt(0, 250000, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        setTestCase(++testCase);
        // CHECK: the statement does not cap the number of test cases; cap total days to keep numeric input size practical.
        ensuref(totalDays + n <= 5000000LL, "total number of profit entries exceeds 5000000");
        totalDays += n;

        for (int i = 0; i < n; ++i) {
            // CHECK: the Korean BOJ statement gives [-10000, 10000], while the legacy English variant says [-100, 100].
            inf.readInt(-10000, 10000, "p");
            inf.readEoln();
        }
    }

    inf.readEof();
}
