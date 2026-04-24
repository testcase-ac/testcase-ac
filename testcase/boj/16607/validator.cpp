#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the only line: the sequence s of moves
    // It must consist of 1 to 20 characters, each one of 'L','R','U','D'
    string s = inf.readLine("[LRUD]{1,20}", "s");

    // No two consecutive characters in s are the same
    int n = (int)s.size();
    for (int i = 1; i < n; i++) {
        // positions are 1-based for error messages
        int p1 = i, p2 = i + 1;
        ensuref(s[i] != s[i-1],
                "Two consecutive identical moves at positions %d and %d: '%c' and '%c'",
                p1, p2, s[i-1], s[i]);
    }

    // The file must end immediately after this single newline
    inf.readEof();
    return 0;
}
