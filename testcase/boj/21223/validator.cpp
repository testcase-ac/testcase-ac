#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    inf.readInt(0, 2000, "k");
    inf.readEoln();

    set<string> words;
    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[a-z]{1,10}", "word");
        inf.readEoln();

        ensuref(words.insert(word).second, "duplicate word at index %d: %s", i + 1, word.c_str());
    }

    inf.readEof();
}
