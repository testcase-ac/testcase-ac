#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    long long D = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    // Read cow positions and heights, ensure distinct positions
    set<long long> xs;
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(1LL, 1000000000LL, "x");
        inf.readSpace();
        long long h = inf.readLong(1LL, 1000000000LL, "h");
        inf.readEoln();

        bool inserted = xs.insert(x).second;
        ensuref(inserted,
                "Duplicate position detected at line %d: x = %lld",
                i + 2, x);
    }

    inf.readEof();
    return 0;
}
