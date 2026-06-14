#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    set<string> title;
    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[a-z]{1,15}", "title_word");
        inf.readEoln();
        ensuref(title.insert(word).second, "duplicate title word at index %d: %s", i + 1, word.c_str());
    }

    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    set<string> heardTitleWords;
    bool guessed = false;
    for (int i = 0; i < m; ++i) {
        string word = inf.readToken("[a-z]{1,15}", "lyric_word");
        inf.readEoln();

        if (title.count(word)) {
            heardTitleWords.insert(word);
        }
        if (2 * static_cast<int>(heardTitleWords.size()) >= n) {
            guessed = true;
        }
    }

    ensuref(guessed, "Mirko never guesses the title from the lyrics");
    inf.readEof();
}
