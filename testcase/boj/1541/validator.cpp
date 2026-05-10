#include "testlib.h"
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the expression: only digits, '+' and '-', length 1 to 50.
    // readLine consumes the end-of-line.
    string s = inf.readLine("[0-9+\\-]{1,50}", "expression");

    int n = (int)s.size();
    // First and last character must be a digit.
    ensuref(isdigit(s[0]),
            "Expression must start with a digit, found '%c' at position 1", s[0]);
    ensuref(isdigit(s[n-1]),
            "Expression must end with a digit, found '%c' at position %d", s[n-1], n);

    // Check that no two operators appear consecutively,
    // and that no number has more than 5 digits.
    int digit_cnt = 0;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (isdigit(c)) {
            digit_cnt++;
            ensuref(digit_cnt <= 5,
                    "Number too long: more than 5 digits ending at position %d", i+1);
        } else {
            // c is '+' or '-'
            // previous char must be a digit (so no two operators, and not at start)
            ensuref(digit_cnt > 0,
                    "Operator '%c' at position %d must follow a digit", c, i+1);
            // reset digit counter for next number
            digit_cnt = 0;
        }
    }
    // After the loop, we must have ended on a digit sequence
    ensuref(digit_cnt > 0, "Expression must end with a digit");

    // No more input after the single line
    inf.readEof();
    return 0;
}
