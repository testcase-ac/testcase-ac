#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 ≤ T ≤ 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Array size N: 1 ≤ N ≤ 1000
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Array values X[i]: |X[i]| < 1000  ⇒  -999 ≤ X[i] ≤ 999
        vector<int> X = inf.readInts(N, -999, 999, "X_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
