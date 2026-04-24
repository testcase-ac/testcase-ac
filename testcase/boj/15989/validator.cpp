#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: must be between 1 and 100000 (inclusive)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read one integer n: 1 <= n <= 10000
    for (int i = 0; i < T; i++) {
        int n = inf.readInt(1, 10000, "n");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
