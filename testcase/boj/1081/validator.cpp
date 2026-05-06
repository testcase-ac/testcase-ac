#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and U
    long long L = inf.readLong(0LL, 2000000000LL, "L");
    inf.readSpace();
    long long U = inf.readLong(0LL, 2000000000LL, "U");
    inf.readEoln();

    // Validate the order constraint
    ensuref(L <= U, "Constraint violation: L (%lld) must be <= U (%lld)", L, U);

    // No more content
    inf.readEof();
    return 0;
}
