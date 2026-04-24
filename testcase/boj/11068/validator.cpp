#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 ≤ T ≤ 100000 (default maximum if unspecified)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test: one integer N, 64 ≤ N ≤ 1,000,000
    for (int i = 1; i <= T; ++i) {
        // We name it "n_i" for clarity; index i is implicit in loop
        inf.readInt(64, 1000000, "n_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
