#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nicknames
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each of the next N lines is a segmented nickname
    for (int i = 1; i <= N; i++) {
        // Read exactly one line: only lowercase letters and spaces, length 1..100
        // We escape the space in the character class as "\ "
        string s = inf.readLine("[a-z\\ ]{1,100}", "nickname");

        // Check total length ≤ 100 (regex already enforces this, but we double check)
        ensuref((int)s.size() <= 100,
                "Line %d: total length %d exceeds 100", i, (int)s.size());

        // Check characters and count spaces
        int space_count = 0;
        for (int j = 0; j < (int)s.size(); j++) {
            char c = s[j];
            ensuref((c >= 'a' && c <= 'z') || c == ' ',
                    "Line %d: invalid character '%c' at position %d", i, c, j + 1);
            if (c == ' ') space_count++;
        }

        // Must contain at least one space (i.e., at least two syllables)
        ensuref(space_count >= 1,
                "Line %d: must contain at least one space", i);
    }

    inf.readEof();
    return 0;
}
