#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lines N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each of the N lines
    for (int i = 0; i < N; i++) {
        // Read one line: must have at least 1 character (the first is alphabet),
        // and overall we will enforce at most 30 characters.
        string s = inf.readLine("[^]+", "line");

        // Check length constraint
        ensuref((int)s.size() <= 30,
                "Line %d has length %d which exceeds 30",
                i+1, (int)s.size());

        for (int j = 0; j < (int)s.size(); ++j) {
            unsigned char c = static_cast<unsigned char>(s[j]);
            ensuref(32 <= c && c <= 126,
                    "Line %d has non-printable ASCII at position %d", i + 1, j + 1);
        }

        // First character must be an ASCII alphabet letter
        char c = s[0];
        ensuref(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'),
                "Line %d starts with non-alphabet character '%c'",
                i+1, c);
        ensuref(s.back() != ' ', "Line %d must not end with a space", i + 1);
        ensuref(s.find("  ") == string::npos,
                "Line %d must not contain repeated spaces", i + 1);
    }

    // File must end immediately after the last newline
    inf.readEof();
    return 0;
}
