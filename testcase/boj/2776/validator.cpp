#include "testlib.h"
#include <vector>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and the N integers for notebook1
        int N = inf.readInt(1, 1000000, "N");
        inf.readEoln();
        vector<int> note1 = inf.readInts(N, (long long)INT_MIN, (long long)INT_MAX, "note1_i");
        inf.readEoln();

        // Read M and the M integers for notebook2
        int M = inf.readInt(1, 1000000, "M");
        inf.readEoln();
        vector<int> note2 = inf.readInts(M, (long long)INT_MIN, (long long)INT_MAX, "note2_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
