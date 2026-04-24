#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly one line: 4 digits (1-9) separated by single spaces, then newline, then EOF.

    // Read exactly 7 characters: digit, space, digit, space, digit, space, digit
    for (int i = 0; i < 7; i++) {
        char c = inf.readChar();
        if (i % 2 == 0) {
            // positions 0,2,4,6: digits '1' to '9'
            ensuref(c >= '1' && c <= '9',
                    "Expected a digit in '1'..'9' at position %d, found '%c'", i+1, c);
        } else {
            // positions 1,3,5: single space
            ensuref(c == ' ',
                    "Expected single space at position %d, found '%c'", i+1, c);
        }
    }

    // After the 7 chars, we must have exactly one newline for the line end.
    inf.readEoln();

    // No more content.
    inf.readEof();
    return 0;
}
