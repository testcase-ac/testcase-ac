#include "testlib.h"
#include <set>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // 2. Read the shuffled, space-removed sentence
        string s = inf.readToken("[a-z]{1,1000}", "shuffled_sentence");
        inf.readEoln();

        // 3. Read n (number of words)
        int n = inf.readInt(1, 10000, "n");
        inf.readEoln();

        set<string> words;
        for (int i = 0; i < n; ++i) {
            string w = inf.readToken("[a-z]{1,100}", "word");
            inf.readEoln();

            // Check for duplicate words
            ensuref(words.insert(w).second, "Duplicate word detected at test case %d, word index %d: '%s'", tc, i+1, w.c_str());
        }
    }

    inf.readEof();
}
