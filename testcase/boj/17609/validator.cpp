#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 ≤ T ≤ 30
    int T = inf.readInt(1, 30, "T");
    inf.readEoln();

    // Each of the next T lines: a non-empty string of lowercase letters, length 3 to 100000
    for (int i = 0; i < T; i++) {
        // Read the entire line; must consist only of lowercase letters
        // We use a loose regex here and then check length with ensuref
        string s = inf.readLine("[a-z]+", "s_i");
        int len = (int)s.size();
        ensuref(len >= 3 && len <= 100000,
                "Length of string at line %d must be between 3 and 100000, but got %d",
                i+2, len);
        // No further checks needed: regex guarantees only 'a'–'z'
    }

    inf.readEof();
    return 0;
}
