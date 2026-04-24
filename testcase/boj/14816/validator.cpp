#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Validate each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // First line of test case: N and P
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int P = inf.readInt(2, 4, "P");
        inf.readEoln();

        // Second line: G_1 ... G_N
        vector<int> G = inf.readInts(N, 1, 100, "G_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
