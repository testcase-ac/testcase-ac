#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases, assume up to 100000 if not specified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a non-empty string of length < 80, only 'O' and 'X'
    for (int tc = 0; tc < T; tc++) {
        // Reads a token consisting only of 'O' and 'X', length 1 to 79
        inf.readToken("[OX]{1,79}", "s");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
