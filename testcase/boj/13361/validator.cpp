#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of plates
    int n = inf.readInt(1, 250000, "n");
    inf.readEoln();

    // Read each plate and validate s_i <= t_i and bounds
    for (int i = 0; i < n; i++) {
        long long s = inf.readLong(1LL, 1000000000LL, "s_i");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readEoln();

        ensuref(s <= t,
                "Constraint violation at plate %d: s_i (%lld) > t_i (%lld)",
                i+1, s, t);
    }

    // No extra data
    inf.readEof();
    return 0;
}
