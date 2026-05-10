#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read each segment and validate
    for (int i = 1; i <= N; i++) {
        // Read start and end coordinates
        long long s = inf.readLong(-1000000000LL, 1000000000LL, "s");
        inf.readSpace();
        long long e = inf.readLong(-1000000000LL, 1000000000LL, "e");
        inf.readEoln();

        // Validate that s < e
        ensuref(s < e,
                "Segment %d is invalid: start point s = %lld must be less than end point e = %lld",
                i, s, e);
    }

    inf.readEof();
    return 0;
}
