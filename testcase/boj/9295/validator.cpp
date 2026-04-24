#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: 1 <= T <= 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read two dice rolls: each between 1 and 6
    for (int i = 1; i <= T; i++) {
        int a = inf.readInt(1, 6, "die1");
        inf.readSpace();
        int b = inf.readInt(1, 6, "die2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
