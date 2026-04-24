#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Read each test case N
    for (int i = 0; i < T; i++) {
        // 1 ≤ N ≤ 1e9
        inf.readLong(1LL, 1000000000LL, "N_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
