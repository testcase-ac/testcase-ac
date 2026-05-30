#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Max N is 10^52 - 1, which has 52 digits
    const string DIGIT_REGEX = "[1-9][0-9]{0,51}";

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Allowed consonants and vowels (as per statement).
    // Each of these is one UTF-8 token in input (testlib readToken() treats them as tokens).
    const set<string> allowedConsonants = {
        "ㄱ","ㄴ","ㄹ","ㅁ","ㅂ","ㅅ","ㅇ","ㅈ","ㅊ","ㅍ","ㅎ"
    };
    const set<string> allowedVowels = {
        "ㅏ","ㅐ","ㅑ","ㅓ","ㅕ","ㅗ","ㅜ","ㅠ","ㅡ","ㅣ"
    };

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read N as a decimal string with canonical rules via regex
        string N = inf.readToken(DIGIT_REGEX, "N");
        // Additional range check: N <= 10^52 - 1 is implied by regex (max 52 digits, first non-zero).
        inf.readSpace();

        int M = inf.readInt(1, 21, "M");
        inf.readEoln();

        // Read M distinct missing jamo, each must be from allowed sets
        set<string> seen;
        for (int i = 0; i < M; ++i) {
            string s = inf.readToken("[^]+", "missing_jamo");
            if (i + 1 < M)
                inf.readSpace();
            else
                inf.readEoln();

            ensuref(s.size() > 0, "Empty jamo token at index %d", i);

            bool isConsonant = allowedConsonants.count(s);
            bool isVowel = allowedVowels.count(s);
            ensuref(isConsonant || isVowel,
                    "Invalid jamo '%s' at index %d: must be one of 11 consonants or 10 vowels",
                    s.c_str(), i);

            ensuref(!seen.count(s),
                    "Duplicate jamo '%s' at index %d (M=%d requires distinct jamo)",
                    s.c_str(), i, M);

            seen.insert(s);
        }

        ensuref((int)seen.size() == M,
                "Number of distinct jamo (%d) does not match M (%d)",
                (int)seen.size(), M);
    }

    inf.readEof();
}
