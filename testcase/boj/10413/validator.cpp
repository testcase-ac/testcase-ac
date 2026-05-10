#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 ≤ T ≤ 10)
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    // For each test case, read one alphabet-only string of length 1..100000
    for (int tc = 1; tc <= T; tc++) {
        // Read the string token: must consist of at least one letter A-Z or a-z
        string s = inf.readToken("[A-Za-z]+", "S");
        int len = (int)s.length();
        // Check length constraint
        ensuref(len <= 100000,
                "Length of string at test case %d is %d, which exceeds 100000",
                tc, len);
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
