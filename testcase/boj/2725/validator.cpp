#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    // Read each test case
    for (int tc = 1; tc <= C; tc++) {
        setTestCase(tc);
        // N: 1 <= N <= 1000
        inf.readInt(1, 1000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
