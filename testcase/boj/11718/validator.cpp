#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    // Read all lines until EOF
    while (!inf.eof()) {
        // Read next line (consumes the newline)
        string s = inf.readLine("[^]+", "line");
        lineCount++;
        // Check number of lines
        ensuref(lineCount <= 100, "Too many lines: %d (max is 100)", lineCount);
        int len = (int)s.size();
        // Check line length constraints
        ensuref(len >= 1 && len <= 100,
                "Length of line %d is %d, but must be between 1 and 100", lineCount, len);
        // No leading or trailing spaces
        ensuref(s[0] != ' ', "Line %d starts with a space", lineCount);
        ensuref(s[len-1] != ' ', "Line %d ends with a space", lineCount);
        // Check allowed characters
        for (int i = 0; i < len; i++) {
            char c = s[i];
            bool ok = (c >= 'a' && c <= 'z')
                   || (c >= 'A' && c <= 'Z')
                   || (c >= '0' && c <= '9')
                   || (c == ' ');
            ensuref(ok,
                    "Invalid character '%c' at line %d position %d: only A-Z, a-z, 0-9, and space are allowed",
                    c, lineCount, i+1);
        }
    }
    // There must be at least one line
    ensuref(lineCount >= 1, "Input must contain at least one non-empty line");
    inf.readEof();
    return 0;
}
