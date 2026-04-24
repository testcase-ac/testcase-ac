#include "testlib.h"
#include <cctype>
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

        // First character must be an ASCII alphabet letter
        char c = s[0];
        ensuref(isalpha(c),
                "Line %d starts with non-alphabet character '%c'",
                i+1, c);
    }

    // File must end immediately after the last newline
    inf.readEof();
    return 0;
}
