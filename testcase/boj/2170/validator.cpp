#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of drawn segments
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // For each drawn segment, read endpoints x < y
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();

        // Ensure the segment is valid (non-degenerate, x < y)
        ensuref(x < y,
                "Segment %d is degenerate or invalid: x (%lld) !< y (%lld)",
                i, x, y);
    }

    // No extra characters after last line
    inf.readEof();
    return 0;
}
