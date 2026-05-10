#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read N and K
        int N = inf.readInt(2, 10000, "N");
        inf.readSpace();
        int K = inf.readInt(2, 10000, "K");
        inf.readEoln();

        // Read frequencies C_i
        vector<int> C = inf.readInts(N, 0, 100000, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
