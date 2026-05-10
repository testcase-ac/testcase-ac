#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int c = inf.readInt(1, 200, "c");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        // Read d and n
        int d = inf.readInt(1, 1000000, "d");
        inf.readSpace();
        int n = inf.readInt(1, 50000, "n");
        inf.readEoln();

        // Read sequence of n integers
        vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
