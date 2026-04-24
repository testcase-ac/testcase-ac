#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    // Each test case: a single integer n
    for (int i = 0; i < t; i++) {
        // 1 <= n <= 1e9
        inf.readInt(1, 1000000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
