#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 0 < N < 1001
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Each test case: two non-empty lowercase strings of length ≤ 1000, separated by one space
    for (int i = 0; i < N; i++) {
        inf.readToken("[a-z]{1,1000}", "s");
        inf.readSpace();
        inf.readToken("[a-z]{1,1000}", "t");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
