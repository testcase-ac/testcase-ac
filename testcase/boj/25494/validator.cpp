#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read a, b, c with given bounds
        int a = inf.readInt(1, 60, "a");
        inf.readSpace();
        int b = inf.readInt(1, 60, "b");
        inf.readSpace();
        int c = inf.readInt(1, 60, "c");
        inf.readEoln();

        // No additional global properties to validate; the problem
        // only constrains ranges of a, b, c and their positivity.
    }

    inf.readEof();
}
