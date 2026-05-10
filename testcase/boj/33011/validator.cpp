#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Validate each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();

        // Read array A of size N
        vector<int> A = inf.readInts(N, 1, 100, "A_i");
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
