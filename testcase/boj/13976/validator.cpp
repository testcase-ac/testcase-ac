#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N can be as large as 1e18, so we must use readLong.
    // Also enforce canonical integer format via readLong.
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readEoln();

    // No further structural constraints (single number input).

    inf.readEof();
}
