#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 1000000, "W");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    long long totalLetters = 0;
    set<string> dictionary;
    for (int i = 1; i <= w; ++i) {
        string word = inf.readToken("[a-z]{1,1000000}", "word");
        inf.readEoln();

        totalLetters += static_cast<long long>(word.size());
        ensuref(totalLetters <= 1000000,
                "total dictionary letters exceeds 1000000 after word %d", i);

        // CHECK: Duplicate dictionary words would make the requested dictionary
        // index ambiguous, so dictionary entries are required to be unique.
        ensuref(dictionary.insert(word).second, "duplicate dictionary word at index %d: %s",
                i, word.c_str());
    }

    for (int i = 1; i <= n; ++i) {
        // CHECK: The statement gives no numeric upper bound for K_i; 1e9 is a
        // practical cap that preserves all meaningful outcomes for this input size.
        inf.readInt(1, 1000000000, "K_i");
        inf.readSpace();
        inf.readToken("[a-z]{1,1000}", "partial_word");
        inf.readEoln();
    }

    inf.readEof();
}
