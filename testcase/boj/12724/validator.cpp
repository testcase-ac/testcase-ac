#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(10, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        int n = inf.readInt(100, 800, "n");
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
