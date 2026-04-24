#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: unspecified in statement, assume 1 to 100000
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        // Read a and b: natural numbers (>=1) up to 1e6
        int a = inf.readInt(1, 1000000, "a");
        // Ensure at least one space between a and b
        inf.readSpace();
        int b = inf.readInt(1, 1000000, "b");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
