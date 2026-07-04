#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<string> words;
    int lineCount = 0;

    while (!inf.eof()) {
        string word = inf.readToken("[a-z]{1,20}", "word");
        inf.readEoln();

        ++lineCount;
        ensuref(words.insert(word).second, "duplicate word on line %d: %s", lineCount, word.c_str());
        ensuref(lineCount <= 10000, "too many words: %d", lineCount);
    }

    ensuref(lineCount >= 2, "input must contain at least two words, found %d", lineCount);
    inf.readEof();
}
