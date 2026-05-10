#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 ≤ T ≤ 10^3
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Each test case: R, G, B, K (each 1 ≤ value ≤ 10^9)
        long long R = inf.readLong(1, 1000000000LL, "R");
        inf.readSpace();
        long long G = inf.readLong(1, 1000000000LL, "G");
        inf.readSpace();
        long long B = inf.readLong(1, 1000000000LL, "B");
        inf.readSpace();
        long long K = inf.readLong(1, 1000000000LL, "K");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
