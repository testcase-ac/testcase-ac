#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a single integer K between 3 and 1000
    for (int i = 0; i < T; i++) {
        inf.readInt(3, 1000, "K");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
