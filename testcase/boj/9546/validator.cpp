#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 <= T <= 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a single integer k (number of stops)
    // Constraint: 1 <= k <= 30
    for (int tc = 0; tc < T; tc++) {
        inf.readInt(1, 30, "k");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
