#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read X and validate
    for (int tc = 0; tc < T; tc++) {
        long long X = inf.readLong(1LL, 1000000000LL, "X");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
