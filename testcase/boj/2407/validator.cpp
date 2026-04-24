#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m according to the problem constraints:
    // 5 ≤ n ≤ 100, 5 ≤ m ≤ 100, and m ≤ n.
    int n = inf.readInt(5, 100, "n");
    inf.readSpace();
    int m = inf.readInt(5, 100, "m");
    ensuref(m <= n, "Constraint violated: m (%d) must be ≤ n (%d)", m, n);
    inf.readEoln();

    // No further input.
    inf.readEof();
    return 0;
}
