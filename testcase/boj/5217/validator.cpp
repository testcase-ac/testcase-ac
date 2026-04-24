#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: 1 <= T < 100
    int T = inf.readInt(1, 99, "T");
    inf.readEoln();

    // Read each test case
    for (int i = 0; i < T; i++) {
        int n = inf.readInt(1, 12, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
