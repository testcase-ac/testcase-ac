#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case: a single integer L
    for (int i = 0; i < T; i++) {
        int L = inf.readInt(1, 5000, "L");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
