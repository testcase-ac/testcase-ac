#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: must be at least 1 and strictly less than 100
    int T = inf.readInt(1, 99, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read first word A: only lowercase letters, length 1 to 100
        inf.readToken("[a-z]{1,100}", "A");
        // Exactly one whitespace between the two words
        inf.readSpace();
        // Read second word B: only lowercase letters, length 1 to 100
        inf.readToken("[a-z]{1,100}", "B");
        // End of this test case line
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
