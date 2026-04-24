#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 50000, "t");
    inf.readEoln();

    // Each test case: one key
    for (int i = 0; i < t; i++) {
        long long k = inf.readLong(1LL, 1000000000000000000LL, "k_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
