#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line (may contain spaces)
    string s = inf.readLine("[^]+", "s");

    int n = (int)s.size();
    // The problem states: length at most 1000, and implicitly at least 1
    ensuref(n >= 1 && n <= 1000,
            "Length of input string must be between 1 and 1000, but is %d", n);

    // No leading or trailing spaces
    ensuref(s[0] != ' ',
            "Leading space is not allowed (first character is space)");
    ensuref(s[n-1] != ' ',
            "Trailing space is not allowed (last character is space)");

    // Characters must be uppercase/lowercase letters or space.
    // Also no consecutive spaces.
    for (int i = 0; i < n; i++) {
        char c = s[i];
        ensuref(isupper(c) || islower(c) || c == ' ',
                "Invalid character at position %d: '%c' (only A-Z, a-z, and space allowed)",
                i + 1, c);
        if (i > 0) {
            ensuref(!(s[i] == ' ' && s[i-1] == ' '),
                    "Consecutive spaces at positions %d and %d are not allowed",
                    i, i + 1);
        }
    }

    // After the single line, there must be EOF immediately.
    inf.readEof();
    return 0;
}
