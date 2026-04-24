#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the text line
    string s = inf.readLine("[^]+", "text");
    int z = (int)s.size();
    // z is total characters including spaces
    ensuref(z >= 1, "Text is empty");
    ensuref(z <= 500000, "Total characters z = %d exceeds 500000", z);

    // No leading or trailing spaces
    ensuref(s.front() != ' ', "Leading space in text");
    ensuref(s.back() != ' ', "Trailing space in text");

    // Only lowercase letters and spaces, and no consecutive spaces
    bool prev_space = false;
    for (int i = 0; i < z; i++) {
        char c = s[i];
        bool is_space = (c == ' ');
        if (is_space && prev_space) {
            ensuref(false, "Consecutive spaces at positions %d and %d", i, i+1);
        }
        prev_space = is_space;
        if (!is_space && !(c >= 'a' && c <= 'z')) {
            ensuref(false, "Invalid character '%c' at position %d", c, i+1);
        }
    }

    // Split into words and compute max word length w
    vector<int> word_lengths;
    word_lengths.reserve(1024);
    int cur = 0;
    for (int i = 0; i <= z; i++) {
        if (i == z || s[i] == ' ') {
            // end of word
            ensuref(cur >= 1, "Empty word detected");
            word_lengths.push_back(cur);
            cur = 0;
        } else {
            cur++;
        }
    }
    ensuref(!word_lengths.empty(), "No words found in text");
    int w = 0;
    for (int len : word_lengths) {
        if (len > w) w = len;
    }
    // w >= 1 by construction

    // Read a and b
    int a = inf.readInt(1, 500000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 500000, "b");
    inf.readEoln();

    // Basic ordering
    ensuref(a <= b, "a (%d) is greater than b (%d)", a, b);
    // Constraints w <= a <= b <= z
    ensuref(a >= w, "a (%d) is less than max word length w (%d)", a, w);
    ensuref(b <= z, "b (%d) is greater than total text length z (%d)", b, z);

    inf.readEof();
    return 0;
}
