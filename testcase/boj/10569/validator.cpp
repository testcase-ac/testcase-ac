#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case: two integers V and E
    for (int tc = 1; tc <= T; tc++) {
        int V = inf.readInt(4, 100, "V");
        inf.readSpace();
        int E = inf.readInt(4, 100, "E");
        inf.readEoln();
        // No further global consistency required:
        // any V,E in the given ranges are accepted per statement.
    }

    inf.readEof();
    return 0;
}
