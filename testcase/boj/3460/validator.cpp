#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Each test case has a single integer n: 1 ≤ n ≤ 10^6
        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
