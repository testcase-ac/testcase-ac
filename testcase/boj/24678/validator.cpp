#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 200000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long x = inf.readLong(1LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(1LL, 1000000000LL, "y");
        inf.readSpace();
        long long z = inf.readLong(1LL, 1000000000LL, "z");
        inf.readEoln();

        // No extra global constraints from the statement to validate.
        // We do not simulate the game since no guarantee like
        // "answer always exists" beyond normal play is stated.
    }

    inf.readEof();
}
