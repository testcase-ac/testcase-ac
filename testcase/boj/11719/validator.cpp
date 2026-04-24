#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    // Read until EOF
    while (true) {
        if (inf.eof()) break;
        // No more than 100 lines
        ensuref(lineCount < 100,
                "Number of lines (%d) exceeds maximum of 100", lineCount + 1);
        // Read one line (excluding the trailing '\n')
        string s = inf.readLine("[^]*", "line");
        // Each line at most 100 characters
        ensuref((int)s.size() <= 100,
                "Length of line %d (%d) exceeds maximum of 100",
                lineCount + 1, (int)s.size());
        // Check allowed characters: lowercase, uppercase, digits, space
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            bool ok = (c == ' ')
                   || ('a' <= c && c <= 'z')
                   || ('A' <= c && c <= 'Z')
                   || ('0' <= c && c <= '9');
            ensuref(ok,
                    "Invalid character '%c' in line %d at position %d; "
                    "only letters, digits, and spaces allowed",
                    c, lineCount + 1, i + 1);
        }
        lineCount++;
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
