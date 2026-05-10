#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int C = inf.readInt(1, 200, "C");
    inf.readEoln();

    for (int tc = 1; tc <= C; ++tc) {
        // Read S
        string S = inf.readToken("[01\\?]{1,100}", "S");
        inf.readEoln();

        // Read T
        string T = inf.readToken("[01]{1,100}", "T");
        inf.readEoln();

        // Check lengths
        ensuref(S.length() == T.length(),
            "Length mismatch in test case %d: S.length()=%zu, T.length()=%zu", tc, S.length(), T.length());

        // Check S only contains '0', '1', '?'
        for (size_t i = 0; i < S.length(); ++i) {
            ensuref(S[i] == '0' || S[i] == '1' || S[i] == '?',
                "Invalid character in S at test case %d, position %zu: '%c'", tc, i+1, S[i]);
        }
        // Check T only contains '0', '1'
        for (size_t i = 0; i < T.length(); ++i) {
            ensuref(T[i] == '0' || T[i] == '1',
                "Invalid character in T at test case %d, position %zu: '%c'", tc, i+1, T[i]);
        }
    }

    inf.readEof();
}
