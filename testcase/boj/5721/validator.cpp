#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (true) {
        // Read M and N (termination when both zero)
        int M = inf.readInt(0, 100000, "M");
        inf.readSpace();
        int N = inf.readInt(0, 100000, "N");
        inf.readEoln();

        // Check for termination line
        if (M == 0 && N == 0) {
            break;
        }

        // This is a real test case
        testCaseCount++;
        ensuref(testCaseCount <= 100000,
                "Number of test cases exceeds limit: %d > 100000",
                testCaseCount);

        // M and N must both be at least 1 for a real test case
        ensuref(M >= 1,
                "M must be at least 1 in test case %d, but got %d",
                testCaseCount, M);
        ensuref(N >= 1,
                "N must be at least 1 in test case %d, but got %d",
                testCaseCount, N);

        // Check product constraint M * N <= 1e5
        long long prod = 1LL * M * N;
        ensuref(prod <= 100000LL,
                "Product M*N exceeds 100000 in test case %d: %d*%d=%lld",
                testCaseCount, M, N, prod);

        // Read the grid: M rows of N candies each
        for (int i = 0; i < M; i++) {
            // Each candy count is between 1 and 1000
            inf.readInts(N, 1, 1000, ("c_row" + to_string(i+1)).c_str());
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
