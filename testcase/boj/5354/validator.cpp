#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: one integer n (1 <= n <= 10)
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 10, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
