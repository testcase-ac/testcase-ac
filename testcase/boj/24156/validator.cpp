#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line, single integer n
    // Constraint: 2 ≤ n ≤ 100000000
    int n = inf.readInt(2, 100000000, "n");
    inf.readEoln();

    // No further constraints in the statement that require simulation or
    // additional global checks: just validate range and format of n.

    inf.readEof();
}
