#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 0 < t < 100  => t in [1,99]
    int t = inf.readInt(1, 99, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; tc++) {
        // Each test case: K and C, both in [1, 1e9]
        long long K = inf.readLong(1LL, 1000000000LL, "K");
        inf.readSpace();
        long long C = inf.readLong(1LL, 1000000000LL, "C");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
