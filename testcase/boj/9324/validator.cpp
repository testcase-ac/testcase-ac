#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: 1 <= T <= 100
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // For each test case, read a single uppercase string of length 1..100000
    for (int tc = 0; tc < T; tc++) {
        // Token must be only uppercase letters, length between 1 and 100000 inclusive
        string s = inf.readToken("[A-Z]{1,100000}", "M");
        inf.readEoln();
        // No further checks needed: regex already constrains characters and length
    }

    inf.readEof();
    return 0;
}
