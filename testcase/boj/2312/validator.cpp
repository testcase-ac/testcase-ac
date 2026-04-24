#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 ≤ T ≤ 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read an integer N (2 ≤ N ≤ 100000) on its own line
    for (int i = 0; i < T; i++) {
        // We name it "N" for clarity; each invocation enforces the bounds
        inf.readInt(2, 100000, "N");
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
