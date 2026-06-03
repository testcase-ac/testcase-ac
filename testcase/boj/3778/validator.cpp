#include "testlib.h"

#include <string>

using namespace std;

void validateWord(const string& word, const char* name) {
    ensuref(word.size() <= 45, "%s length must be at most 45, found %d", name,
            static_cast<int>(word.size()));
    for (int i = 0; i < static_cast<int>(word.size()); ++i) {
        ensuref('a' <= word[i] && word[i] <= 'z',
                "%s contains non-lowercase letter at position %d", name, i + 1);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 59999, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);
        string a = inf.readLine();
        string b = inf.readLine();
        validateWord(a, "first_word");
        validateWord(b, "second_word");
    }

    inf.readEof();
}
