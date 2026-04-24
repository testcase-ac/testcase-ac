#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of sentences
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read the whole line as the sentence
        string s = inf.readLine("[^]+", "sentence");
        // Check maximum length 100
        ensuref((int)s.size() <= 100,
                "Sentence %d is too long: length = %d, max = 100",
                i+1, (int)s.size());
        // No leading or trailing spaces
        ensuref(!s.empty() && s.front() != ' ',
                "Sentence %d has leading space", i+1);
        ensuref(!s.empty() && s.back() != ' ',
                "Sentence %d has trailing space", i+1);
        // No multiple consecutive spaces
        ensuref(s.find("  ") == string::npos,
                "Sentence %d has multiple consecutive spaces", i+1);
        // Count words (spaces + 1)
        int words = 1;
        for (char c : s) {
            if (c == ' ')
                words++;
        }
        ensuref(words >= 3,
                "Sentence %d has too few words: %d (min = 3)",
                i+1, words);
    }

    inf.readEof();
    return 0;
}
