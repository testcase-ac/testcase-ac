#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    // Each test case: a single natural number N (1 ≤ N ≤ 1,000,000)
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 1000000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
