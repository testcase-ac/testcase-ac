#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: a single integer N (0 <= N <= 40)
    for (int i = 0; i < T; i++) {
        int N = inf.readInt(0, 40, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
