#include "testlib.h"

#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long totalLength = 0;
    unordered_set<string> words;
    words.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        string word = inf.readToken("[a-z]+", "word");
        inf.readEoln();

        totalLength += static_cast<long long>(word.size());
        ensuref(totalLength <= 1000000LL,
                "total word length exceeds 1000000 after word %d", i + 1);
        ensuref(words.insert(word).second, "duplicate word at index %d: %s", i + 1,
                word.c_str());
    }

    string s = inf.readToken("[a-z]+", "s");
    ensuref(3 <= static_cast<int>(s.size()) && static_cast<int>(s.size()) <= 3000000,
            "s length must be between 3 and 3000000, got %d",
            static_cast<int>(s.size()));
    inf.readEoln();

    inf.readEof();
}
