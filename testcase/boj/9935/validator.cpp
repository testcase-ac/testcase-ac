#include "testlib.h"
#include <set>
#include <string>
#include <cctype>
using namespace std;

// Helper to check allowed characters
bool isAllowedChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: main string S
    string S = inf.readLine("[^]{1,1000000}", "S");
    ensuref(1 <= (int)S.size() && (int)S.size() <= 1000000, "Length of S (%d) is out of bounds", (int)S.size());
    for (int i = 0; i < (int)S.size(); ++i) {
        ensuref(isAllowedChar(S[i]), "S contains invalid character at position %d: '%c'", i+1, S[i]);
    }

    // Read second line: explosion string E
    string E = inf.readLine("[^]{1,36}", "E");
    ensuref(1 <= (int)E.size() && (int)E.size() <= 36, "Length of E (%d) is out of bounds", (int)E.size());
    for (int i = 0; i < (int)E.size(); ++i) {
        ensuref(isAllowedChar(E[i]), "E contains invalid character at position %d: '%c'", i+1, E[i]);
    }

    // Check that E does not contain any character more than once
    set<char> e_chars;
    for (int i = 0; i < (int)E.size(); ++i) {
        char c = E[i];
        ensuref(e_chars.count(c) == 0, "Explosion string E contains duplicate character '%c' at position %d", c, i+1);
        e_chars.insert(c);
    }

    inf.readEof();
}
