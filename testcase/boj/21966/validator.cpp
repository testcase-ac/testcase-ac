#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // 2. Read S (must be exactly N characters, no whitespace)
    string S = inf.readLine("[A-Za-z,\\.]{2,100000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);

    // 3. Check first and last character
    ensuref(S[0] != '.', "First character of S is a period ('.'), which is not allowed");
    ensuref(S[N-1] == '.', "Last character of S is not a period ('.')");

    // 4. Check all characters are allowed (already checked by regex, but double-check for clarity)
    for (int i = 0; i < N; ++i) {
        char c = S[i];
        ensuref(isupper(c) || islower(c) || c == ',' || c == '.', "Invalid character '%c' at position %d", c, i+1);
    }

    // 5. No whitespace in S (guaranteed by regex and readLine)

    inf.readEof();
}
