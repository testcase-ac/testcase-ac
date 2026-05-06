#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    // Each test case: one string of uppercase letters, length < 1000
    for (int tc = 1; tc <= T; tc++) {
        // Read a token consisting of 1 to 999 uppercase letters (A-Z)
        inf.readToken("[A-Z]{1,999}", "s");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
