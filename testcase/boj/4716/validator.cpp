#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tcCount = 0;
    while (true) {
        // Read N, A, B
        int N = inf.readInt(0, 1000, "N");
        inf.readSpace();
        int A = inf.readInt(0, 10000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 10000, "B");
        inf.readEoln();

        // Sentinel check
        if (N == 0) {
            // Must be exactly the sentinel
            ensuref(A == 0 && B == 0,
                    "When N=0 (sentinel), A and B must both be 0 (got A=%d, B=%d)", A, B);
            break;
        }

        // Count test cases
        tcCount++;
        ensuref(tcCount <= 100000,
                "Number of test cases exceeds 100000 (now %d)", tcCount);
        setTestCase(tcCount);

        // Validate N for a real test case
        ensuref(N >= 1,
                "N must be at least 1 for a real test case (got N=%d)", N);
        // A, B already in [0,10000] by readInt

        // Read the N team lines
        __int128 sumK = 0;
        for (int i = 0; i < N; i++) {
            int K = inf.readInt(0, A + B, "K_i");
            inf.readSpace();
            int DA = inf.readInt(0, 1000, "D_A_i");
            inf.readSpace();
            int DB = inf.readInt(0, 1000, "D_B_i");
            inf.readEoln();

            sumK += K;
        }
        // Validate total balloons needed does not exceed storage
        long long totalStorage = (long long)A + (long long)B;
        ensuref(sumK <= totalStorage,
                "Sum of all K_i (%lld) exceeds A+B (%lld)",
                (long long)sumK, totalStorage);
    }

    inf.readEof();
    return 0;
}
