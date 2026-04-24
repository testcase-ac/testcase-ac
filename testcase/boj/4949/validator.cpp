#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect up to 100000 test lines plus 1 sentinel line "."
    int totalLines = 0;
    while (true) {
        // Read the next line (must contain at least one character)
        string s = inf.readLine("[^]+", "line");
        totalLines++;
        // Enforce the limit on number of lines (test cases + sentinel)
        ensuref(totalLines <= 100001,
                "Too many lines: expected at most 100000 test cases plus 1 sentinel, got %d lines",
                totalLines);

        // Check for sentinel: a line consisting of exactly "."
        if (s == ".") {
            break;
        }

        // For any non-sentinel line, enforce length 2..100 (including the final dot)
        int n = (int)s.size();
        ensuref(n >= 2 && n <= 100,
                "Line %d: length must be between 2 and 100 (inclusive), got %d",
                totalLines, n);

        // The last character must be a dot '.'
        ensuref(s[n-1] == '.',
                "Line %d: must end with a period '.', got '%c' at position %d",
                totalLines, s[n-1], n);

        // All preceding characters must be: letters (A-Z, a-z), space, or one of ()[].
        for (int i = 0; i < n-1; i++) {
            char c = s[i];
            bool ok = ( (c >= 'A' && c <= 'Z')
                        || (c >= 'a' && c <= 'z')
                        || c == ' '
                        || c == '(' || c == ')' 
                        || c == '[' || c == ']');
            ensuref(ok,
                    "Line %d, position %d: invalid character '%c'",
                    totalLines, i+1, c);
        }
    }

    inf.readEof();
    return 0;
}
