#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read k
        int k = inf.readInt(1, 14, "k");
        inf.readEoln();

        // Read n
        int n = inf.readInt(1, 14, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
