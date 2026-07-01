#include "testlib.h"

#include <cctype>
#include <string>
using namespace std;

namespace {

bool isAsciiLetter(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

void ensurePrintableAsciiLine(const string& line, const char* name) {
    ensuref(!line.empty(), "%s must not be empty", name);
    ensuref(line.size() <= 100, "%s exceeds 100 characters", name);

    for (int i = 0; i < int(line.size()); ++i) {
        unsigned char c = static_cast<unsigned char>(line[i]);
        ensuref(32 <= c && c <= 126,
                "%s contains non-printable ASCII at position %d",
                name,
                i + 1);
    }
}

bool containsWord(const string& line) {
    for (char c : line) {
        if (isAsciiLetter(c)) {
            return true;
        }
    }
    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int p = inf.readInt(1, 100, "P");
        inf.readEoln();

        for (int i = 1; i <= p; ++i) {
            string word = inf.readLine("[A-Za-z]{1,100}", "pleasant_word");
            ensuref(word.size() <= 100, "pleasant word %d exceeds 100 characters", i);
        }

        int l = inf.readInt(1, 100, "L");
        inf.readEoln();

        bool hasWord = false;
        for (int i = 1; i <= l; ++i) {
            string line = inf.readLine("[^]{1,100}", "song_line");
            ensurePrintableAsciiLine(line, "song line");
            hasWord = hasWord || containsWord(line);
        }

        // CHECK: The statement defines pleasantness as a percentage of words, so
        // a valid song needs at least one word to make that percentage defined.
        ensuref(hasWord, "song must contain at least one word");
    }

    inf.readEof();
}
