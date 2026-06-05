#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Za-z]{1,50}", "s");
    inf.readEoln();

    for (int i = 1; i < (int)s.size(); ++i) {
        ensuref(islower((unsigned char)s[i]), "s[%d] must be lowercase: %c", i, s[i]);
    }

    bool hasLowercaseVowel = false;
    for (char c : s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            hasLowercaseVowel = true;
        }
    }
    ensuref(hasLowercaseVowel, "s must contain at least one lowercase vowel");

    inf.readEof();
}
