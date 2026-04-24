#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line input (the encrypted string)
    // Use a permissive regex to grab the entire line, then validate length and characters
    string s = inf.readLine("[^]*", "s");

    // Constraint: length between 1 and 31 inclusive
    ensuref(s.size() >= 1 && s.size() <= 31,
            "The input string length must be between 1 and 31, but found %d", (int)s.size());

    // Constraint: each character must be one of:
    //   - binary digits '0' or '1'
    //   - operators '+', '-', '*'
    //   - parentheses '(' or ')'
    //   - equal sign '='
    //   - Roman letters 'A'-'Z' or 'a'-'z'
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        bool ok = false;
        if (c == '0' || c == '1' ||
            c == '+' || c == '-' || c == '*' ||
            c == '=' ||
            c == '(' || c == ')')
            ok = true;
        else if ('A' <= c && c <= 'Z')
            ok = true;
        else if ('a' <= c && c <= 'z')
            ok = true;
        ensuref(ok, "Invalid character '%c' at position %d", c, i + 1);
    }

    // After the single line, there must be no extra data
    inf.readEof();
    return 0;
}
