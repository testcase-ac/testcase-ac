#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Each test case: a single integer N
    for (int i = 0; i < T; i++) {
        setTestCase(i + 1);
        inf.readLong(1LL, 1000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
