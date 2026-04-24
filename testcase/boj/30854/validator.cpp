#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m, n
    int m = inf.readInt(4, 100000, "m");
    inf.readSpace();
    int n = inf.readInt(0, 100000, "n");
    inf.readEoln();

    // Read the v_i sequence
    vector<long long> v = inf.readLongs(m, 0LL, 1000000LL, "v");
    inf.readEoln();

    // Check v1 = 0 and v_m = 0
    ensuref(v.front() == 0LL, "v1 must be 0, found %lld", v.front());
    ensuref(v.back()  == 0LL, "v_m must be 0, found %lld", v.back());

    // Read pest points
    for (int i = 0; i < n; i++) {
        long long x = inf.readLong(0LL, 1000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000LL, "y");
        inf.readEoln();
        // We do not check exact containment in the polygon here,
        // but we ensure the coordinates are within the allowed range.
    }

    inf.readEof();
    return 0;
}
