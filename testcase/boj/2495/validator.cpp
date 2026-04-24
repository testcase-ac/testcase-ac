#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem specifies exactly three lines, each an eight‐digit positive integer.
    for (int i = 1; i <= 3; i++) {
        // Read one line: exactly 8 digits, no spaces.
        string s = inf.readLine("[0-9]{8}", "number");
        // Ensure it's a valid positive 8-digit number (no leading zero).
        ensuref(s[0] != '0',
                "Line %d: leading zero is not allowed in an eight‐digit positive integer (got \"%s\")",
                i, s.c_str());
    }

    // After exactly three lines, there must be no extra characters.
    inf.readEof();
    return 0;
}
