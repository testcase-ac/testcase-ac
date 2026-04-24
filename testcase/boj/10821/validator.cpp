#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: only digits and commas, length between 1 and 100
    string S = inf.readLine("[0-9,]{1,100}", "S");

    // Check that S starts and ends with a digit (not a comma)
    ensuref(isdigit(S.front()),
            "The first character of S must be a digit, found '%c'", S.front());
    ensuref(isdigit(S.back()),
            "The last character of S must be a digit, found '%c'", S.back());

    int n = (int)S.size();

    // Check no consecutive commas
    ensuref(S.find(",,") == string::npos,
            "S must not contain consecutive commas");

    // Check no leading zeros in any integer
    // We split S on commas and check each token
    int start = 0;
    for (int i = 0; i <= n; ++i) {
        if (i == n || S[i] == ',') {
            int len = i - start;
            // token is S[start .. i-1], len >= 1
            ensuref(len >= 1,
                    "Empty token detected between positions %d and %d", start, i);
            if (len > 1 && S[start] == '0') {
                // leading zero violation
                ensuref(false,
                        "Integer token starting at position %d has a leading zero: \"%.*s\"",
                        start, len, S.c_str() + start);
            }
            start = i + 1;
        }
    }

    // No extra characters: we've consumed the only line including its newline
    inf.readEof();
    return 0;
}
