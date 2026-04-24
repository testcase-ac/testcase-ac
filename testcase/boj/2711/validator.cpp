#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 <= T <= 1000
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Each test case: one line with an integer pos and an uppercase string S
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // pos: 1 <= pos <= 80 (we'll further check against actual string length)
        int pos = inf.readInt(1, 80, "pos");
        inf.readSpace();

        // S: uppercase letters only, length between 1 and 80
        string s = inf.readToken("[A-Z]{1,80}", "s");
        inf.readEoln();

        // Ensure the position is within the string length
        ensuref(pos <= (int)s.length(),
                "In test case %d, pos = %d exceeds string length = %d",
                tc, pos, (int)s.length());
    }

    inf.readEof();
    return 0;
}
