#include "testlib.h"

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<string> initials = {
        "r", "R", "s", "e", "E", "f", "a", "q", "Q", "t",
        "T", "d", "w", "W", "c", "z", "x", "v", "g",
    };
    const vector<string> vowels = {
        "k", "o", "i", "O", "j", "p", "u", "P", "h", "hk", "ho",
        "hl", "y", "n", "nj", "np", "nl", "b", "m", "ml", "l",
    };
    const vector<string> finals = {
        "",   "r",  "R",  "rt", "s",  "sw", "sg", "e",  "f",  "fr",
        "fa", "fq", "ft", "fx", "fv", "fg", "a",  "q",  "qt", "t",
        "T",  "d",  "w",  "c",  "z",  "x",  "v",  "g",
    };

    vector<unordered_set<string>> syllables_by_length(6);
    for (const string& initial : initials) {
        for (const string& vowel : vowels) {
            for (const string& final : finals) {
                string keys = initial + vowel + final;
                syllables_by_length[keys.size()].insert(keys);
            }
        }
    }

    string s = inf.readLine("[^]{1,10000}", "s");
    for (int i = 0; i < int(s.size()); ++i) {
        char ch = s[i];
        bool allowed = ch == ' ' || ('a' <= ch && ch <= 'z') ||
                       ch == 'O' || ch == 'P' || ch == 'Q' ||
                       ch == 'R' || ch == 'T' || ch == 'W' ||
                       ch == 'E';
        ensuref(allowed, "invalid keyboard character at index %d: %c", i + 1, ch);
    }

    // CHECK: The statement allows spaces inside the Hangul string but does not
    // specify whether leading, trailing, repeated, or whitespace-only strings
    // are valid. Treat spaces as ordinary word separators under local defaults.
    ensuref(s.front() != ' ', "s must not start with a space");
    ensuref(s.back() != ' ', "s must not end with a space");
    ensuref(s.find("  ") == string::npos, "s must not contain consecutive spaces");

    vector<char> reachable(s.size() + 1, false);
    reachable[0] = true;
    for (int i = 0; i < int(s.size()); ++i) {
        if (!reachable[i]) {
            continue;
        }
        if (s[i] == ' ') {
            reachable[i + 1] = true;
            continue;
        }
        for (int len = 2; len <= 5 && i + len <= int(s.size()); ++len) {
            string part = s.substr(i, len);
            if (syllables_by_length[len].count(part)) {
                reachable[i + len] = true;
            }
        }
    }

    ensuref(reachable[s.size()],
            "s must be segmentable into complete Hangul syllable keystrokes and spaces");

    inf.readEof();
}
