#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2500, "n");
    inf.readEoln();

    vector<string> correct;
    correct.reserve(n);
    set<string> remaining;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        string word = inf.readToken("[a-z]{3,15}", "correct_i");
        ensuref(remaining.insert(word).second,
                "duplicate word in correct order at index %d: %s", i + 1, word.c_str());
        correct.push_back(word);
    }
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        string word = inf.readToken("[a-z]{3,15}", "answer_i");
        ensuref(remaining.count(word) == 1,
                "answer word at index %d is not in correct order: %s", i + 1, word.c_str());
        ensuref(seen.insert(word).second,
                "duplicate word in answer order at index %d: %s", i + 1, word.c_str());
    }
    inf.readEoln();

    inf.readEof();
}
