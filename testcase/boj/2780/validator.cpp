#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // For each test, read N: the length of the password
        inf.readInt(1, 1000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
