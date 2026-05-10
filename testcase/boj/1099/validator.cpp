#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read the sentence
    string sentence = inf.readToken("[a-z]{1,50}", "sentence");
    inf.readEoln();

    // 2. Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // 3. Read N words
    vector<string> words;
    for (int i = 0; i < N; ++i) {
        string word = inf.readToken("[a-z]{1,50}", "word");
        inf.readEoln();
        words.push_back(word);
    }

    // 4. Check all words are lowercase, length 1~50 (already checked by regex)
    // 5. Check sentence is lowercase, length 1~50 (already checked by regex)

    // 6. No further global constraints (e.g., no requirement for words to be unique, see sample input 4)

    inf.readEof();
}
