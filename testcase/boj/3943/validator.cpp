#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read a single integer n
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 100000, "n");
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
