#include "testlib.h"
#include <algorithm>
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    set<string> words;
    string canonical;
    for (int i = 0; i < n; ++i) {
        string w = inf.readToken("[a-z]{1,26}", "w");
        inf.readEoln();

        set<char> letters(w.begin(), w.end());
        ensuref(letters.size() == w.size(),
                "word %d contains duplicate letters: %s", i + 1, w.c_str());

        ensuref(words.insert(w).second,
                "duplicate word at line %d: %s", i + 2, w.c_str());

        string sorted = w;
        sort(sorted.begin(), sorted.end());
        if (i == 0) {
            canonical = sorted;
        } else {
            ensuref(sorted == canonical,
                    "word %d is not an anagram of the first word: %s",
                    i + 1, w.c_str());
        }
    }

    inf.readEof();
    return 0;
}
