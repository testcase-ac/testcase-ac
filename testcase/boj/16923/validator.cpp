#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the word S
    string S = inf.readToken("[a-z]{1,26}", "S");
    inf.readEoln();

    // Check that all characters are unique (all different lowercase letters)
    set<char> seen;
    for (int i = 0; i < (int)S.size(); ++i) {
        char c = S[i];
        ensuref('a' <= c && c <= 'z', "Character at position %d is not a lowercase letter: '%c'", i+1, c);
        ensuref(seen.count(c) == 0, "Duplicate character '%c' found at position %d", c, i+1);
        seen.insert(c);
    }

    inf.readEof();
}
