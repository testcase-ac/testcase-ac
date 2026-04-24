#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 8, "n");
        inf.readEoln();

        // Read first vector
        vector<int> v1 = inf.readInts(n, -1000, 1000, "x_i");
        inf.readEoln();

        // Read second vector
        vector<int> v2 = inf.readInts(n, -1000, 1000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
