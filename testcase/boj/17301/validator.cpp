#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<string> words;
    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[A-Z]{1,10}", "word");
        inf.readEoln();

        ensuref(word.find('N') != string::npos || word.find('C') != string::npos,
                "word %d must contain at least one N or C: %s", i + 1, word.c_str());
        ensuref(words.insert(word).second, "duplicate word at index %d: %s", i + 1, word.c_str());
    }

    inf.readEof();
}
