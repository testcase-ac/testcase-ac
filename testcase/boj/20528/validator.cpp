#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N palindrome strings
    for (int i = 0; i < N; i++) {
        // Construct a name for better error messages
        string name = "S_" + to_string(i+1);
        // Read one token: lowercase letters only, length 1..100
        string s = inf.readToken("[a-z]{1,100}", name.c_str());
        // Check that s is a palindrome
        int m = (int)s.size();
        for (int j = 0; j < m/2; j++) {
            ensuref(s[j] == s[m-1-j],
                    "String %s is not a palindrome: mismatch at positions %d and %d ('%c' != '%c')",
                    name.c_str(), j+1, m-j, s[j], s[m-1-j]);
        }
        // After each string except the last, there must be exactly one space
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            // After the last string, we must end the line
            inf.readEoln();
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
