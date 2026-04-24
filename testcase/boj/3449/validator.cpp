#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: 1 <= T <= 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read two binary strings, length between 1 and 100, only '0' or '1'
        string s1 = inf.readLine("[01]{1,100}", "s1");
        string s2 = inf.readLine("[01]{1,100}", "s2");

        // Ensure both strings have the same length
        ensuref(s1.length() == s2.length(),
                "Lengths mismatch in test case %d: len(s1)=%d, len(s2)=%d",
                tc, (int)s1.length(), (int)s2.length());
    }

    inf.readEof();
    return 0;
}
