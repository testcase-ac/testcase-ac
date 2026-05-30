#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readInts(M, 0, 1000, "initial_pigs");
    inf.readEoln();

    long long totalKeys = 0;
    for (int i = 1; i <= N; i++) {
        // CHECK: A has no written upper bound. Allow repeated nondecreasing key
        // tokens, but keep total key-token count within a practical input size.
        int A = inf.readInt(0, 5000000, "A_i");
        totalKeys += A;
        ensuref(totalKeys <= 5000000,
                "too many key tokens by customer %d: %lld", i, totalKeys);
        int previousKey = 0;
        for (int j = 1; j <= A; j++) {
            inf.readSpace();
            int k = inf.readInt(1, M, "key_i_j");
            // CHECK: The English statement says keys are sorted nondecreasingly,
            // so equal adjacent key tokens are accepted rather than rejected.
            ensuref(previousKey <= k,
                    "keys for customer %d are not nondecreasing at position %d", i, j);
            previousKey = k;
        }
        inf.readSpace();
        // CHECK: B has no written upper bound; cap it to the natural 32-bit
        // demand scale used by this legacy problem data and reference code.
        inf.readLong(0LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
