#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the algorithm name line: only letters and hyphens, length 1 to 100
    string s = inf.readLine("[A-Za-z-]{1,100}", "S");
    int n = (int)s.size();

    // First character must be uppercase
    ensuref(isupper(s[0]),
            "First character must be uppercase, found '%c' at position 1", s[0]);

    // Validate the rest of the pattern
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '-') {
            // Hyphen must not be last, and must be followed by an uppercase letter
            ensuref(i + 1 < n,
                    "Hyphen at position %d cannot be the last character", i + 1);
            char nxt = s[i+1];
            ensuref(isupper(nxt),
                    "Character after hyphen at position %d must be uppercase, found '%c'",
                    i + 1, nxt);
        }
        else if (isupper(c)) {
            // Uppercase letters allowed only at start or immediately after a hyphen
            if (i != 0) {
                ensuref(s[i-1] == '-',
                        "Uppercase letter '%c' at position %d must follow a hyphen",
                        c, i + 1);
            }
        }
        else if (islower(c)) {
            // Lowercase letters are not allowed immediately after a hyphen
            if (i > 0 && s[i-1] == '-') {
                ensuref(false,
                        "Lowercase letter '%c' at position %d must be uppercase after hyphen",
                        c, i + 1);
            }
        }
        else {
            // Should never happen due to the regex, but just in case
            ensuref(false,
                    "Invalid character '%c' at position %d", c, i + 1);
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}
