#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: not specified in statement => assume 1 ≤ T ≤ 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and X
        int N = inf.readInt(1, 500000, "N");
        inf.readSpace();
        int X = inf.readInt(-1000000000, 1000000000, "X");
        inf.readEoln();

        // Read the sequence of length N
        vector<int> a = inf.readInts(N, -1000000000, 1000000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
