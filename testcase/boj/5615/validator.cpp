#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of catalog entries, allow 0 to 100000
    int N = inf.readInt(0, 100000, "N");
    inf.readEoln();

    // Read the N area values, one per line, check ascending order
    long long prev = 0;  // since area >= 1
    for (int i = 0; i < N; i++) {
        long long area = inf.readLong(1LL, 2147483647LL, "area");
        inf.readEoln();
        if (i > 0) {
            ensuref(area > prev,
                    "Catalog not strictly increasing at index %d: %lld !> %lld",
                    i, area, prev);
        }
        prev = area;
    }

    inf.readEof();
    return 0;
}
