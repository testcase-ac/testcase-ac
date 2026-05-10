#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N is a single integer on the first line: even, 2 ≤ N ≤ 150000000
    int N = inf.readInt(2, 150000000, "N");
    inf.readEoln();

    // Check that N is even, as required by the statement.
    ensuref(N % 2 == 0, "N must be even, but got %d", N);

    // No further structural constraints; single test case only.
    inf.readEof();
}
