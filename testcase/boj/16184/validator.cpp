#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 2000, "T");
    inf.readEoln();

    // For each test case, read N and validate range
    for (int tc = 0; tc < T; tc++) {
        long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
