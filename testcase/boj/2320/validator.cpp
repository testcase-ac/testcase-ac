#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 16, "N");
    inf.readEoln();

    set<string> words;
    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[AEIOU]{1,100}", "word");
        inf.readEoln();

        ensuref(words.insert(word).second, "duplicate word at index %d: %s", i + 1, word.c_str());
    }

    inf.readEof();
}
