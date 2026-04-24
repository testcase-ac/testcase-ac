#include "testlib.h"
#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line S
    string s = inf.readLine("[^]+", "S");
    int n = (int)s.size();
    // Check length constraint
    ensuref(n <= 100000, "Length of S is %d, but must be <= 100000", n);
    // Check start/end are not spaces
    ensuref(n > 0, "S must be non-empty");
    ensuref(s[0] != ' ', "S must not start with a space");
    ensuref(s[n-1] != ' ', "S must not end with a space");

    bool inTag = false;
    int tagStart = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        // Allowed characters
        bool okChar = (c >= 'a' && c <= 'z')
                   || (c >= '0' && c <= '9')
                   || c == ' ' || c == '<' || c == '>';
        ensuref(okChar, "Invalid character '%c' at position %d", c, i);

        if (c == '<') {
            // Must not already be in a tag
            ensuref(!inTag, "Nested '<' at position %d", i);
            inTag = true;
            tagStart = i;
        }
        else if (c == '>') {
            // Must be inside a tag
            ensuref(inTag, "Closing '>' without matching '<' at position %d", i);
            // Check tag length >= 3
            int tlen = i - tagStart + 1;
            ensuref(tlen >= 3, 
                    "Tag from %d to %d is too short (length %d), must be >= 3", 
                    tagStart, i, tlen);
            inTag = false;
        }
        else if (inTag) {
            // Inside a tag: only lowercase letters or spaces
            ensuref((c == ' ') || (c >= 'a' && c <= 'z'),
                    "Invalid character '%c' inside tag at position %d", c, i);
        }
        else {
            // Outside tags: must be lowercase, digit, or space (angles handled above)
            if (c == ' ') {
                // Space must separate two alphanumeric characters (single space between words)
                ensuref(i-1 >= 0 && i+1 < n,
                        "Space at position %d must have characters on both sides", i);
                char l = s[i-1], r = s[i+1];
                ensuref(isalnum(l) && isalnum(r),
                        "Space at position %d must be between two alphanumeric characters, got '%c' and '%c'",
                        i, l, r);
            }
            else {
                // letter or digit
                ensuref(isalnum(c),
                        "Invalid character '%c' outside tag at position %d", c, i);
            }
        }
    }
    // All tags must be closed
    ensuref(!inTag, "Unclosed '<' starting at position %d", tagStart);

    // Check no '>' appears before any '<'
    // (this is already enforced: a '>' outside a tag is invalid)

    // Check no spaces adjacent to tags: covered because spaces must be between alnum,
    // so next to '<' or '>' would fail the alnum check.

    // No nested tags or mismatched counts: enforced above.

    // Final EOF check
    inf.readEof();
    return 0;
}
