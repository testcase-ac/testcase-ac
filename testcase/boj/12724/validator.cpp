#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T, 1 <= T <= 10
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read n: vector size 1 <= n <= 800
        int n = inf.readInt(1, 800, "n");
        inf.readEoln();

        // Read first vector v1
        vector<int> v1 = inf.readInts(n, -100000, 100000, "x_i");
        inf.readEoln();

        // Read second vector v2
        vector<int> v2 = inf.readInts(n, -100000, 100000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
