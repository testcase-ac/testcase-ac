#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input line (the string to be typed)
    string s = inf.readLine("[A-Za-z]{1,3000}", "s");

    // Check that the string length is within bounds
    int n = int(s.size());
    ensuref(1 <= n && n <= 3000, "String length %d is out of bounds [1, 3000]", n);

    // Check that all characters are English letters (redundant with regex, but for clarity)
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        ensuref(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'),
            "Character at position %d ('%c') is not an English letter", i + 1, c);
    }

    inf.readEof();
}
