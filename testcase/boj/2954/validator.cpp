#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line: must be 1 to 100 characters of lowercase letters or spaces.
    // Note: in testlib regex, space inside character class must be escaped as '\ '.
    string s = inf.readLine(R"([a-z\ ]{1,100})", "s");
    int n = (int)s.size();
    ensuref(n >= 1 && n <= 100,
            "Length of the sentence must be between 1 and 100, found %d", n);

    // No leading or trailing spaces
    ensuref(s.front() != ' ',
            "Leading space is not allowed");
    ensuref(s.back() != ' ',
            "Trailing space is not allowed");

    // Check characters and no consecutive spaces
    for (int i = 0; i < n; i++) {
        char c = s[i];
        ensuref((c >= 'a' && c <= 'z') || c == ' ',
                "Invalid character at position %d: '%c'", i, c);
        if (c == ' ') {
            // not last character
            ensuref(i + 1 < n,
                    "Space at position %d is the last character", i);
            // no two spaces in a row
            ensuref(s[i + 1] != ' ',
                    "Consecutive spaces at positions %d and %d", i, i + 1);
        }
    }

    // No extra input
    inf.readEof();
    return 0;
}
