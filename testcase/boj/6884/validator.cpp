#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; tc++) {
        // Read n
        int n = inf.readInt(1, 10000, "n");
        // Read the sequence elements, each preceded by exactly one space
        for (int i = 0; i < n; i++) {
            inf.readSpace();
            inf.readInt(0, 10000, "a_i");
        }
        // End of this test case line
        inf.readEoln();
    }

    // No extra characters after all test cases
    inf.readEof();
    return 0;
}
