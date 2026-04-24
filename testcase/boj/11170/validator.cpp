#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    // Read each test case
    for (int tc = 0; tc < T; tc++) {
        // N and M with 0 ≤ N ≤ M ≤ 1,000,000
        int N = inf.readInt(0, 1000000, "N_i");
        inf.readSpace();
        int M = inf.readInt(N, 1000000, "M_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
