#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem has a single test case: two integers M and N on one line.
    // Constraints: 2 ≤ M, N ≤ 100000.

    int M = inf.readInt(2, 100000, "M");
    inf.readSpace();
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // No additional structural/global properties are specified that must
    // hold for the input beyond the numeric constraints above. The rest
    // (counting ways, modulo, etc.) is for the solution, not the validator.

    inf.readEof();
}
