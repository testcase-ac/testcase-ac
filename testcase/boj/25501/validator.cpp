#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // For each test case, read the string S
    // S must consist of 1 to 1000 uppercase letters [A-Z] only
    for (int tc = 0; tc < T; tc++) {
        inf.readLine("[A-Z]{1,1000}", "S");
    }

    inf.readEof();
    return 0;
}
