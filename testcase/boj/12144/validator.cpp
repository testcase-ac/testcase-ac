#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Helper: split line into words by single space
vector<string> split_words(const string& line) {
    vector<string> words;
    size_t pos = 0, prev = 0;
    while (pos <= line.size()) {
        if (pos == line.size() || line[pos] == ' ') {
            words.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        ++pos;
    }
    return words;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 25, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 200, "N");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            // Read the line as arbitrary string (no regex), then check all constraints manually
            string line = inf.readLine("[^]+", "sentence_line");

            // 1. Not empty
            ensuref(!line.empty(), "Sentence line %d in test case %d is empty", i+1, tc);

            // 2. No leading/trailing spaces
            ensuref(line.front() != ' ' && line.back() != ' ',
                "Sentence line %d in test case %d has leading or trailing spaces", i+1, tc);

            // 3. No double spaces
            for (size_t j = 1; j < line.size(); ++j) {
                ensuref(!(line[j-1] == ' ' && line[j] == ' '),
                    "Sentence line %d in test case %d has consecutive spaces at position %zu", i+1, tc, j-1);
            }

            // 4. All characters are lowercase or space
            for (size_t j = 0; j < line.size(); ++j) {
                char c = line[j];
                ensuref(islower(c) || c == ' ',
                    "Invalid character '%c' (ASCII %d) in sentence line %d in test case %d at position %zu", c, int(c), i+1, tc, j);
            }

            // 5. Split into words and check each word
            vector<string> words = split_words(line);

            // 6. Each word: non-empty, <=10, all lowercase
            for (size_t w = 0; w < words.size(); ++w) {
                const string& word = words[w];
                ensuref(!word.empty(), "Empty word in sentence line %d in test case %d at word %zu", i+1, tc, w+1);
                ensuref(word.size() <= 10,
                    "Word '%s' in sentence line %d in test case %d exceeds 10 characters", word.c_str(), i+1, tc);
                for (char c : word) {
                    ensuref(islower(c),
                        "Non-lowercase letter '%c' in word '%s' in sentence line %d in test case %d", c, word.c_str(), i+1, tc);
                }
            }

            // 7. Number of words per sentence
            if (i == 0 || i == 1) {
                // First two sentences: 1..1000 words
                ensuref(words.size() >= 1 && words.size() <= 1000,
                    "Sentence %d in test case %d must have 1 to 1000 words, got %zu", i+1, tc, words.size());
            } else {
                // Other sentences: 1..10 words
                ensuref(words.size() >= 1 && words.size() <= 10,
                    "Sentence %d in test case %d must have 1 to 10 words, got %zu", i+1, tc, words.size());
            }
        }
    }

    inf.readEof();
}
