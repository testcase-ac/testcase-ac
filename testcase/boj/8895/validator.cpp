#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: not specified, assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        inf.setTestCase(tc + 1);

        // Read n, l, r with constraints: 1 ≤ l, r ≤ n ≤ 20
        int n = inf.readInt(1, 20, "n");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
