#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: 1 <= t < 10
    int t = inf.readInt(1, 9, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; tc++) {
        setTestCase(tc);
        // Each test case has one integer N: 3 <= N <= 9
        int N = inf.readInt(3, 9, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
