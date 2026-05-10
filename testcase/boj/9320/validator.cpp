#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Read 4 integers in [1,9]
        inf.readInts(4, 1, 9, "a b c d");
        inf.readEoln();
    }

    inf.readEof();
}
