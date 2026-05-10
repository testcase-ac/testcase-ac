#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire line as the input string S
    // We'll validate allowed characters and spacing manually
    string S = inf.readLine("[^]+", "S");

    // Check length constraints
    int n = (int)S.size();
    ensuref(1 <= n && n <= 100000,
            "Length of S must be between 1 and 100000, but got %d", n);

    // Validate characters and spacing
    for (int i = 0; i < n; i++) {
        char c = S[i];
        bool okChar = (c >= 'a' && c <= 'z')
                   || (c >= 'A' && c <= 'Z')
                   || c == ' ' || c == '!' || c == '-';
        ensuref(okChar, "Invalid character at position %d: '%c'", i+1, c);
        if (i > 0) {
            ensuref(!(S[i] == ' ' && S[i-1] == ' '),
                    "Consecutive spaces at positions %d and %d", i, i+1);
        }
    }

    // After the single line, no more input
    inf.readEof();
    return 0;
}
