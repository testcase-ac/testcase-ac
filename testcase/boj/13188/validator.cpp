#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int cs = inf.readInt(1, n, "cs");
    inf.readSpace();
    int cf = inf.readInt(1, n, "cf");
    inf.readEoln();

    ensuref(cs != cf, "cs and cf must be distinct");

    bool hasRoute = true;
    if (n == 2) {
        hasRoute = true;
    } else if (n % 2 == 1) {
        hasRoute = !((cs == 1 && cf == n) || (cs == n && cf == 1));
    } else {
        hasRoute = !((cs == 1 && cf == 2) || (cs == 2 && cf == 1) ||
                     (cs == n - 1 && cf == n) || (cs == n && cf == n - 1));
    }
    ensuref(hasRoute, "no alternating route exists for N=%d, cs=%d, cf=%d", n, cs, cf);

    inf.readEof();
}
