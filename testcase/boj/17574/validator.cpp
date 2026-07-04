#include "testlib.h"

#include <cmath>

using namespace std;

namespace {
constexpr long long kMaxValue = 1000000000000000000LL;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, kMaxValue, "n");
    inf.readSpace();
    inf.readLong(1LL, kMaxValue, "m");
    inf.readSpace();
    double f = inf.readDouble(0.0, 1.0, "f");
    ensuref(f > 0.0, "f must be greater than 0, found %.17g", f);
    ensuref(isfinite(f), "f must be finite");
    inf.readEoln();
    inf.readEof();

    // CHECK: the statement guarantees a unique best value, but verifying that
    // exactly over up to 10^18 possible door counts is outside validator scope.
}
