#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int B = inf.readInt(N, 1000000, "B");
    inf.readEoln();

    // Constraints:
    // 1 <= A <= 10^6
    // 1 <= N <= B <= 10^6

    // Additional checks:
    ensuref(B >= N, "B (%d) must be >= N (%d)", B, N);

    inf.readEof();
}
