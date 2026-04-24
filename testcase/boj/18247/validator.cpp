#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Each test: N (number of rows), M (seats per row)
        int N = inf.readInt(1, 26, "N");
        inf.readSpace();
        int M = inf.readInt(1, 9, "M");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
