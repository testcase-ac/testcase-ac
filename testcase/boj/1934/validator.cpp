#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // For each test case, read A and B
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 45000, "A");
        inf.readSpace();
        inf.readInt(1, 45000, "B");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
