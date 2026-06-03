#include "testlib.h"

#include <string>

using namespace std;

bool isLetter(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool isPunctuation(char c) {
    return c == '!' || c == '?' || c == ',' || c == '.';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    int totalWords = 0;
    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        string line = inf.readLine("[^]+", "sentence");
        ensuref(int(line.size()) <= 300000, "sentence %d is too long", i);
        ensuref(line.front() != ' ', "sentence %d has leading space", i);
        ensuref(line.back() != ' ', "sentence %d has trailing space", i);

        int wordsInLine = 0;
        int pos = 0;

        while (pos < int(line.size())) {
            ensuref(line[pos] != ' ', "sentence %d has repeated spaces", i);

            int start = pos;
            int letters = 0;
            while (pos < int(line.size()) && isLetter(line[pos])) {
                ++letters;
                ++pos;
            }
            ensuref(letters > 0, "sentence %d word %d has no alphabet letters", i, wordsInLine + 1);

            bool hasPunctuation = false;
            char punctuation = 0;
            if (pos < int(line.size()) && isPunctuation(line[pos])) {
                hasPunctuation = true;
                punctuation = line[pos];
                ++pos;
            }

            int tokenLength = pos - start;
            ensuref(tokenLength <= 50, "sentence %d word %d length is %d", i, wordsInLine + 1, tokenLength);

            ++wordsInLine;
            ++totalWords;
            ensuref(totalWords <= 5000, "total word count exceeds 5000");

            bool isLastToken = pos == int(line.size());
            if (isLastToken) {
                ensuref(hasPunctuation && punctuation == '.', "sentence %d last word must end with period", i);
            } else {
                ensuref(pos < int(line.size()) && line[pos] == ' ',
                        "sentence %d word %d is not followed by one space", i, wordsInLine);
                ensuref(punctuation != '.', "sentence %d has period before the last word", i);
                ++pos;
                ensuref(pos < int(line.size()), "sentence %d has trailing space", i);
                ensuref(line[pos] != ' ', "sentence %d has repeated spaces", i);
            }
        }

        ensuref(wordsInLine >= 1, "sentence %d has no words", i);
    }

    inf.readEof();
}
