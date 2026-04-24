#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the word: only lowercase letters, '-' and '=', length 1 to 100
    string s = inf.readToken("[a-z=-]{1,100}", "word");
    inf.readEoln();

    // Validate that the word can be decomposed into valid Croatian alphabet tokens
    // Special tokens: "dz=", "c=", "c-", "d-", "lj", "nj", "s=", "z="
    // Otherwise single lowercase letter
    set<string> two = {"c=", "c-", "d-", "lj", "nj", "s=", "z="};
    int n = (int)s.size();
    int i = 0;
    while (i < n) {
        // Try 3-character token "dz="
        if (i + 2 < n && s[i] == 'd' && s[i+1] == 'z' && s[i+2] == '=') {
            i += 3;
        }
        // Try any of the 2-character tokens
        else if (i + 1 < n) {
            string sub2 = s.substr(i, 2);
            if (two.count(sub2)) {
                i += 2;
            } else {
                // Single character must be a lowercase letter
                ensuref(s[i] >= 'a' && s[i] <= 'z',
                        "Invalid single character '%c' at position %d", s[i], i);
                i += 1;
            }
        }
        // Last character: must be a lowercase letter
        else {
            ensuref(s[i] >= 'a' && s[i] <= 'z',
                    "Invalid single character '%c' at position %d", s[i], i);
            i += 1;
        }
    }

    // End of file check: exactly one newline after the word, then EOF
    inf.readEof();
    return 0;
}
