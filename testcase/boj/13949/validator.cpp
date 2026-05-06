#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: two integers k and n
    // Constraints: 2 ≤ k ≤ 1000, 1 ≤ n ≤ 1000
    int k = inf.readInt(2, 1000, "k");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // No further input specified; single test case only.
    // All numeric tokens are standard integers, so canonical form
    // (no leading zeros etc.) is already enforced by readInt.

    inf.readEof();
}
