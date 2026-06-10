#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxWords = 30000;
    constexpr int kMaxTotalWordChars = 10000000;

    int word_count = 0;
    int total_word_chars = 0;
    while (!inf.eof()) {
        string word = inf.readToken("[a-z]{1,10000000}", "word");
        inf.readEoln();
        ++word_count;
        ensuref(word_count <= kMaxWords, "word count is greater than %d", kMaxWords);
        // CHECK: The statement gives no word length bound; cap total input text
        // at the local string-heavy default to keep validation practical.
        total_word_chars += (int)word.size();
        ensuref(total_word_chars <= kMaxTotalWordChars,
                "total word length is greater than %d", kMaxTotalWordChars);
    }

    ensuref(word_count > 0, "input must contain at least one word");
    inf.readEof();
}
