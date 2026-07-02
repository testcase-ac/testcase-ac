#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<string> words;
    for (int i = 1; i <= m; ++i) {
        string word = inf.readToken("[a-z]{1,20}", "word");
        inf.readEoln();

        ensuref(words.insert(word).second,
                "duplicate word at index %d: %s",
                i,
                word.c_str());
    }

    inf.readEof();
}
