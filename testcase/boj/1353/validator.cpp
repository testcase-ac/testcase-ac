#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers S and P.
    // "S와 P는 1,000,000,000보다 작거나 같은 자연수이다."
    // -> S, P are natural numbers in [1, 1e9].
    long long S = inf.readLong(1LL, 1000000000LL, "S");
    inf.readSpace();
    long long P = inf.readLong(1LL, 1000000000LL, "P");
    inf.readEoln();

    // No further global properties are guaranteed in the statement:
    // we do NOT check existence of any list or simulate anything,
    // since that is the solution's task. The statement also does not
    // guarantee e.g. that an answer always exists, so no extra checks.

    inf.readEof();
}
