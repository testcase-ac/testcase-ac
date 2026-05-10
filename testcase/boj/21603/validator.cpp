#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers N and K
    long long N = inf.readLong(1LL, 100000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, 100000LL, "K");
    inf.readEoln();

    // No further structural/global guarantees to check:
    // - No graph / connectivity
    // - No "answer always exists" beyond trivial (there is always a well-defined set,
    //   possibly empty), so nothing to simulate or compute here.

    inf.readEof();
}
