#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Read each test case
    for (int i = 0; i < T; i++) {
        inf.readInt(10, 100000, "N");
        inf.readEoln();
    }

    // Ensure no extra data
    inf.readEof();
    return 0;
}
