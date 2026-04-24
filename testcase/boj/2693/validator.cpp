#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // For each test case, read exactly 10 integers between 1 and 1000
    for (int tc = 0; tc < T; tc++) {
        inf.readInts(10, 1, 1000, "A");
        inf.readEoln();
    }

    // Ensure no extra data
    inf.readEof();
    return 0;
}
