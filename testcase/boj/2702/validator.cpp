#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Read each test case
    for (int i = 1; i <= T; i++) {
        // Dynamic names for better error messages
        string aName = "a_" + to_string(i);
        string bName = "b_" + to_string(i);

        // Read a_i and b_i in [1, 1000]
        inf.readInt(1, 1000, aName.c_str());
        inf.readSpace();
        inf.readInt(1, 1000, bName.c_str());
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
