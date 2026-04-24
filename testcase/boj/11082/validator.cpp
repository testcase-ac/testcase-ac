#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single token representing the decimal string
    string s = inf.readToken("[^]+", "s");
    inf.readEoln();

    int n = (int)s.size();
    // Length constraint
    ensuref(n <= 10, "Length of input (%d) exceeds 10", n);
    ensuref(n >= 1, "Input is empty");

    // Count special characters
    int cnt_dot = 0, cnt_op = 0, cnt_cl = 0;
    int pos_dot = -1, pos_op = -1, pos_cl = -1;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '.') {
            cnt_dot++;
            pos_dot = i;
        } else if (c == '(') {
            cnt_op++;
            pos_op = i;
        } else if (c == ')') {
            cnt_cl++;
            pos_cl = i;
        } else if (c >= '0' && c <= '9') {
            // ok
        } else {
            ensuref(false, "Invalid character '%c' at position %d", c, i);
        }
    }

    ensuref(cnt_dot <= 1, "More than one decimal point found");
    ensuref(cnt_op <= 1, "More than one '(' found");
    ensuref(cnt_cl <= 1, "More than one ')' found");
    // Parentheses must match
    ensuref(cnt_op == cnt_cl, "Mismatched parentheses: '(' count = %d, ')' count = %d", cnt_op, cnt_cl);

    // No sign allowed
    if (s[0] == '+' || s[0] == '-') {
        ensuref(false, "Signed numbers not allowed");
    }

    // If there is a parenthesis, enforce its position relative to dot
    if (cnt_op == 1) {
        // Must have a decimal point before '('
        ensuref(cnt_dot == 1, "Found '(' at position %d but no decimal point", pos_op);
        // '(' must come after '.'
        ensuref(pos_op > pos_dot, "'(' at %d must come after decimal point at %d", pos_op, pos_dot);
        // ')' must come after '('
        ensuref(pos_cl > pos_op, "')' at %d must come after '(' at %d", pos_cl, pos_op);
        // At least one digit in the repeating part
        ensuref(pos_cl - pos_op - 1 >= 1, "Empty repeating part '()' at positions %d-%d", pos_op, pos_cl);
        // No characters after ')'
        ensuref(pos_cl == n - 1, "Characters found after ')' at position %d", pos_cl);
    }

    if (cnt_dot == 1) {
        // There must be at least one digit before the decimal point
        ensuref(pos_dot >= 1, "No integer part before decimal point at position %d", pos_dot);
        // Validate integer-part digits
        for (int i = 0; i < pos_dot; i++) {
            ensuref(isdigit(s[i]), "Non-digit '%c' in integer part at position %d", s[i], i);
        }
        // Validate the part after the decimal point
        if (cnt_op == 1) {
            // Non-repeating fractional part: between dot and '('
            for (int i = pos_dot + 1; i < pos_op; i++) {
                ensuref(isdigit(s[i]), "Non-digit '%c' in non-repeating fractional part at position %d", s[i], i);
            }
            // Repeating part: between '(' and ')'
            for (int i = pos_op + 1; i < pos_cl; i++) {
                ensuref(isdigit(s[i]), "Non-digit '%c' in repeating part at position %d", s[i], i);
            }
        } else {
            // No parentheses => all digits after dot
            ensuref(pos_dot < n - 1, "No fractional digits after decimal point at position %d", pos_dot);
            for (int i = pos_dot + 1; i < n; i++) {
                ensuref(isdigit(s[i]), "Non-digit '%c' in fractional part at position %d", s[i], i);
            }
        }
    } else {
        // No decimal point: entire string must be digits, and no parentheses allowed
        ensuref(cnt_op == 0 && cnt_cl == 0, "Parentheses found without decimal point");
        for (int i = 0; i < n; i++) {
            ensuref(isdigit(s[i]), "Non-digit '%c' in integer string at position %d", s[i], i);
        }
    }

    inf.readEof();
    return 0;
}
