#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        // Read number of lines in this program part: n >= 0
        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();
        if (n == 0) {
            // termination marker
            break;
        }
        ++testCases;
        ensuref(testCases <= 100000,
                "Number of program parts exceeds 100000: %d", testCases);

        // Each of the next n lines must be exactly "x = y"
        // where x,y are lowercase letters.
        for (int i = 0; i < n; i++) {
            inf.readToken("[a-z]", "lhs_variable");
            inf.readSpace();
            inf.readToken("=", "equals_sign");
            inf.readSpace();
            inf.readToken("[a-z]", "rhs_variable");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
