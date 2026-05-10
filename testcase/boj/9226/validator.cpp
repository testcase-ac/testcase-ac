#include "testlib.h"
#include <string>
using namespace std;

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_LEN = 20;
    const int MAX_LINES = 100000;

    int line_cnt = 0;
    while (true) {
        string s = inf.readLine("[a-z#]{1,20}", "word_or_hash");
        ++line_cnt;
        ensuref(line_cnt <= MAX_LINES + 1, "Too many lines: %d (max %d + 1 for '#')", line_cnt, MAX_LINES);

        // Check for '#' line
        if (s == "#") {
            break;
        }

        // Check length
        ensuref(1 <= int(s.size()) && int(s.size()) <= MAX_LEN, "Word length out of bounds at line %d: %d", line_cnt, int(s.size()));

        // Check all lowercase
        for (size_t i = 0; i < s.size(); ++i) {
            ensuref('a' <= s[i] && s[i] <= 'z', "Non-lowercase character at line %d, position %zu: '%c'", line_cnt, i + 1, s[i]);
        }
    }

    // After '#' line, must be EOF
    inf.readEof();
}
