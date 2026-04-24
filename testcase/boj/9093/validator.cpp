#include "testlib.h"
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    const int MAX_T = 100000;
    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read the entire line (sentence). We allow any chars except newline,
        // then enforce our own constraints below.
        string s = inf.readLine("[^]+", "s");

        // Check length constraints
        ensuref(!s.empty(), "Line %d is empty", tc);
        ensuref((int)s.size() <= 1000, 
                "Line %d length %d exceeds maximum of 1000", tc, (int)s.size());

        // No leading or trailing spaces
        ensuref(s.front() != ' ', "Line %d has leading space", tc);
        ensuref(s.back()  != ' ', "Line %d has trailing space", tc);

        // Check characters and split into words
        int cur_len = 0;
        int word_count = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            // Only alphabetic or space allowed
            ensuref(isalpha(c) || c == ' ',
                    "Line %d has invalid character '%c' at position %d", tc, c, i+1);

            if (c == ' ') {
                // No consecutive spaces
                ensuref(i+1 == (int)s.size() || s[i+1] != ' ',
                        "Line %d has multiple consecutive spaces at position %d", tc, i+1);
                // Check the word we just finished
                ensuref(cur_len >= 1, 
                        "Line %d has an empty word before space at position %d", tc, i+1);
                ensuref(cur_len <= 20,
                        "Line %d has a word of length %d > 20 ending at position %d", 
                        tc, cur_len, i);
                word_count++;
                cur_len = 0;
            } else {
                // Building a word
                cur_len++;
            }
        }
        // Last word checks
        ensuref(cur_len >= 1,
                "Line %d has an empty last word", tc);
        ensuref(cur_len <= 20,
                "Line %d has a last word of length %d > 20", tc, cur_len);
        word_count++;

        // Proceed to next line (the EOLN was consumed by readLine)
    }

    inf.readEof();
    return 0;
}
