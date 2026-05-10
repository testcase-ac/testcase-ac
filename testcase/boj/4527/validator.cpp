#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of data sets
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Constants
    const long long YARD_INCHES = 36LL * 36LL; // 1296

    for (int tc = 0; tc < N; ++tc) {
        setTestCase(tc + 1);

        int I = inf.readInt(1, 10, "I");
        inf.readEoln();

        long long totalSetArea = 0;
        for (int i = 0; i < I; ++i) {
            int S = inf.readInt(1, 1000, "S");
            inf.readSpace();
            int R = inf.readInt(1, 100, "R");
            inf.readEoln();

            totalSetArea += 1LL * S * R;
        }

        // Ensure that at least one full set fits in 3 square yards
        // Because output always exists and is finite.
        long long maxArea = 3LL * YARD_INCHES;
        ensuref(totalSetArea > 0, "Total set area must be positive");
        ensuref(totalSetArea <= maxArea,
                "Total area of one full set (%lld) must not exceed 3 square yards (%lld)",
                totalSetArea, maxArea);
    }

    inf.readEof();
}
