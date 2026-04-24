#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case consists of one integer k
    // Constraint: 2 <= k <= 1299709 (the 100000-th prime)
    for (int i = 0; i < T; i++) {
        inf.readInt(2, 1299709, "k");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
