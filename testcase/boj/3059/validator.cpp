#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a single string S of uppercase letters, length 1 to 1000
    for (int tc = 0; tc < T; tc++) {
        // Read S: must consist only of 'A'..'Z', length between 1 and 1000
        inf.readToken("[A-Z]{1,1000}", "S");
        inf.readEoln();
    }

    // No extra content after last test case
    inf.readEof();
    return 0;
}
