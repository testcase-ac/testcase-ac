#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and P
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int P = inf.readInt(2, 3, "P");
        inf.readEoln();

        // Read the group sizes G_i
        vector<int> G = inf.readInts(N, 1, 100, "G_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
