#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int wordCount = 0;
    while (!inf.eof()) {
        inf.readToken("[a-z]{1,20}", "word");
        inf.readEoln();
        ++wordCount;

        // CHECK: The statement gives no line-count bound; cap primarily textual input at 100000 lines.
        ensuref(wordCount <= 100000, "too many words: %d", wordCount);
    }

    ensuref(wordCount >= 1, "input must contain at least one word");
    inf.readEof();
}
