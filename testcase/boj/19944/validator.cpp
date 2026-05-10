#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test: two positive integers N and M on one line.
    // Constraints from statement:
    // 3 ≤ N ≤ 1000
    // 1 ≤ M ≤ 1000

    int N = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // No additional global properties or hidden constraints.

    inf.readEof();
}
