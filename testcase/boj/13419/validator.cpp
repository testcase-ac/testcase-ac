#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: not specified, assume up to 100,000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read the game string: uppercase letters only, length 1 to 26
        string s = inf.readToken("[A-Z]{1,26}", "S");
        inf.readEoln();

        // Check distinctness of letters
        vector<bool> seen(26, false);
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - 'A';
            ensuref(!seen[c], "Duplicate character '%c' in test case %d at position %d", s[i], tc, i+1);
            seen[c] = true;
        }
    }

    inf.readEof();
    return 0;
}
