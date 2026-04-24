#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; ++tc) {
        setTestCase(tc + 1);

        // Number of shops
        int n = inf.readInt(1, 20, "n");
        inf.readEoln();

        // Positions of shops
        vector<int> x = inf.readInts(n, 0, 99, "x_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
