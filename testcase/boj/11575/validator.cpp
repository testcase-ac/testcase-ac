#include "testlib.h"
#include <string>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read a and b
        int a = inf.readInt(1, 1000000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 1000000, "b");
        inf.readEoln();

        // Validate that a is coprime with 26
        ensuref(std::gcd(a, 26) == 1,
                "In test case %d: a = %d is not coprime with 26", tc+1, a);

        // Read plaintext string s: must be uppercase letters only, length in (0, 1e6)
        string s = inf.readToken("[A-Z]+", "s");
        inf.readEoln();
        ensuref(!s.empty(),
                "In test case %d: plaintext string is empty", tc+1);
        ensuref((int)s.size() < 1000000,
                "In test case %d: |s| = %d is not less than 1,000,000", tc+1, (int)s.size());
    }

    inf.readEof();
    return 0;
}
