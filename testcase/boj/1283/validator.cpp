#include "testlib.h"
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    for (int line = 1; line <= N; ++line) {
        // Read the entire line (allow any character, check constraints manually)
        string s = inf.readLine("[^]+", "option line");

        // 2. Check for leading/trailing spaces
        ensuref(!s.empty(), "Line %d: Option line is empty", line);
        ensuref(s.front() != ' ', "Line %d: Leading space is not allowed", line);
        ensuref(s.back() != ' ', "Line %d: Trailing space is not allowed", line);

        // 3. Check for multiple consecutive spaces
        for (size_t i = 1; i < s.size(); ++i) {
            ensuref(!(s[i-1] == ' ' && s[i] == ' '), "Line %d: Multiple consecutive spaces detected", line);
        }

        // 4. Split into words
        vector<string> words;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        ensuref(1 <= (int)words.size() && (int)words.size() <= 5, "Line %d: Number of words must be between 1 and 5, found %d", line, (int)words.size());

        for (size_t wi = 0; wi < words.size(); ++wi) {
            string& w = words[wi];
            ensuref(1 <= (int)w.size() && (int)w.size() <= 10, "Line %d: Word %d length must be between 1 and 10, found %d", line, (int)wi+1, (int)w.size());
            for (char c : w) {
                ensuref(isalpha(c), "Line %d: Word %d contains non-alphabet character '%c'", line, (int)wi+1, c);
            }
        }
    }

    inf.readEof();
}
