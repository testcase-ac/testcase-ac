#include "testlib.h"
#include <string>
using namespace std;

static bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine(R"([a-z\ ]{1,100})", "s");
    int n = (int)s.size();
    ensuref(n >= 1 && n <= 100,
            "Length of the sentence must be between 1 and 100, found %d", n);

    ensuref(s.front() != ' ',
            "Leading space is not allowed");
    ensuref(s.back() != ' ',
            "Trailing space is not allowed");

    for (int i = 0; i < n; i++) {
        char c = s[i];
        ensuref((c >= 'a' && c <= 'z') || c == ' ',
                "Invalid character at position %d: '%c'", i, c);
        if (c == ' ') {
            // not last character
            ensuref(i + 1 < n,
                    "Space at position %d is the last character", i);
            // no two spaces in a row
            ensuref(s[i + 1] != ' ',
                    "Consecutive spaces at positions %d and %d", i, i + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!isVowel(s[i])) {
            continue;
        }
        ensuref(i + 2 < n,
                "Vowel at position %d is not followed by a full encoded triplet", i);
        ensuref(s[i + 1] == 'p' && s[i + 2] == s[i],
                "Vowel at position %d is not followed by p and the same vowel", i);
        i += 2;
    }

    inf.readEof();
    return 0;
}
