#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int K = inf.readInt(1, 15, "K");
    inf.readEoln();

    for (int tc = 1; tc <= K; tc++) {
        setTestCase(tc);
        // Read N and M
        int N = inf.readInt(2, 300, "N");
        inf.readSpace();
        int M = inf.readInt(2, 5000, "M");
        inf.readEoln();

        // Sum of capacities in this test case
        long long sumCaps = 0;

        // Read edges
        for (int i = 0; i < M; i++) {
            int f = inf.readInt(1, N, "f");
            inf.readSpace();
            int t = inf.readInt(1, N, "t");
            inf.readSpace();
            int b = inf.readInt(1, 999, "b"); // b < 1000, assume b >= 1
            inf.readEoln();

            sumCaps += b;
        }

        // Global constraint: sum of all capacities in this test <= 20000
        ensuref(sumCaps <= 20000,
                "Sum of capacities in test case %d is %lld, which exceeds 20000",
                tc, sumCaps);
    }

    inf.readEof();
    return 0;
}
