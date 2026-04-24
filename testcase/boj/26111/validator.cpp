#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the parentheses string: only '(' and ')' allowed
    string s = inf.readToken("[()]+", "s");
    int n = (int)s.size();
    // Check length constraints
    ensuref(n >= 2 && n <= 10000000,
            "Length of s must be between 2 and 1e7, found %d", n);

    // Check that the parentheses form exactly one balanced tree:
    // - prefix depth never negative
    // - no prefix before the last where depth == 0 (to avoid multiple components)
    // - final depth == 0
    int depth = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            depth++;
        } else { // s[i] == ')'
            depth--;
        }
        ensuref(depth >= 0,
                "Too many closing parentheses at position %d: depth %d",
                i+1, depth);
        if (i < n-1) {
            ensuref(depth > 0,
                    "Multiple root parentheses detected: depth zero at position %d",
                    i+1);
        }
    }
    ensuref(depth == 0,
            "Unbalanced parentheses: final depth is %d instead of 0", depth);

    // No extra characters: the line must end here
    inf.readEoln();
    inf.readEof();
    return 0;
}
