#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: one line string s with no spaces
    // Use a safe "match anything" regex; we'll check contents manually.
    string s = inf.readLine("[^]+", "s");

    int n = (int)s.size();
    ensuref(1 <= n && n <= 1000000,
            "Length of s must be between 1 and 1,000,000, got %d", n);

    // The string must consist only of uppercase 'A' and 'B'
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        ensuref(c == 'A' || c == 'B',
                "s[%d] is '%c', but must be either 'A' or 'B'", i + 1, c);
    }

    // After the single line, there must be EOF (no extra lines or spaces)
    inf.readEof();
}
