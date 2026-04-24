#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read N: number of days
        int N = inf.readInt(2, 1000000, "N");
        inf.readEoln();
        // Read stock prices for N days
        inf.readInts(N, 1, 10000, "price");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
