#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: first and only line contains N and M
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // No further structural constraints are implied that depend on N, M,
    // and the statement does not guarantee additional properties (like
    // connectivity, existence of some structure in the input, etc.) that
    // must be enforced by simulation or computation on the input.
    // Therefore, basic range checks and format strictness are sufficient.

    inf.readEof();
}
