#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and C
    int L = inf.readInt(3, 15, "L");
    inf.readSpace();
    int C = inf.readInt(3, 15, "C");
    ensuref(L <= C, "L (%d) must be <= C (%d)", L, C);
    inf.readEoln();

    // Read exactly C lowercase letters, separated by exactly one whitespace
    set<char> seen;
    for (int i = 0; i < C; i++) {
        // read one lowercase letter
        string tok = inf.readToken("[a-z]", "letter");
        ensuref(tok.size() == 1, "letter token must be exactly one character, got '%s'", tok.c_str());
        char ch = tok[0];
        ensuref('a' <= ch && ch <= 'z', "letter must be lowercase a-z, got '%c'", ch);
        ensuref(!seen.count(ch), "duplicate letter detected: '%c'", ch);
        seen.insert(ch);

        // consume whitespace: space before next letter, or end-of-line after last
        if (i + 1 < C) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // No more content
    inf.readEof();
    return 0;
}
