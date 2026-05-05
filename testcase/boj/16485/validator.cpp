#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers c and b on the first line.
    // c, b are positive integers <= 1e9.
    long long c = inf.readLong(1LL, 1000000000LL, "c");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "b");
    inf.readEoln();

    // Geometrically, for any positive b, c there exists a triangle ABC
    // with AB = c, AC = b (take any angle at A), so no extra feasibility
    // constraints are needed beyond positivity.

    inf.readEof();
}
