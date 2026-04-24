#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: unspecified in statement, so assume 1 ≤ T ≤ 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read n: 1 ≤ n ≤ 1,000,000
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 1000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
