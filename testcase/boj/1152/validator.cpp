#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire line (may be empty, up to the newline).
    string s = inf.readLine("[^]*", "s");

    // Check length constraint
    ensuref((int)s.size() <= 1000000, "The length of the string is %d, but must be at most 1000000", (int)s.size());
    ensuref(s.size() > 0, "String cannot be empty");

    // Check characters and no consecutive spaces
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        ensuref((c == ' ') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'),
                "Invalid character '%c' at position %d: only English letters and spaces are allowed", c, i);
        if (i > 0) {
            ensuref(!(s[i] == ' ' && s[i-1] == ' '),
                    "Consecutive spaces detected at positions %d and %d", i-1, i);
        }
    }
    ensuref(!(s.size() == 1 && s[0] == ' '), "String cannot be all blank");

    // Final EOF check
    inf.readEof();
    return 0;
}
