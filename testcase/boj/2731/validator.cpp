#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read S as a token of 1 to 10 digits
        string S = inf.readToken("[0-9]{1,10}", "S");
        inf.readEoln();

        int len = (int)S.size();
        // Check no leading zeros unless it's exactly "0" (but "0" isn't in allowed endings anyway)
        ensuref(!(len > 1 && S[0] == '0'),
                "Leading zero detected in S at test %d: \"%s\"", tc+1, S.c_str());
        // Check length ≤ 10 (redundant given regex, but clearer)
        ensuref(len <= 10,
                "Length of S exceeds 10 at test %d: \"%s\"", tc+1, S.c_str());
        // Check last digit ∈ {1,3,7,9}
        char last = S[len-1];
        ensuref(last == '1' || last == '3' || last == '7' || last == '9',
                "Last digit of S is not one of {1,3,7,9} at test %d: \"%s\"", tc+1, S.c_str());
    }

    inf.readEof();
    return 0;
}
