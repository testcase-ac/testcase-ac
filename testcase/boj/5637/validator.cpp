#include "testlib.h"
#include <cctype>
#include <vector>
#include <string>
#include <inttypes.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read all lines until EOF
    vector<string> lines;
    while (!inf.eof()) {
        // Read a line (may be empty)
        string line = inf.readLine("[^]*", "line");
        lines.push_back(line);
    }
    // There must be at least one line
    ensuref(!lines.empty(), "Input is empty");

    // Check total characters <= 10000 (excluding newline chars)
    long long total_chars = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        total_chars += (long long)lines[i].size();
        ensuref(total_chars <= 10000LL,
                "Total number of characters up to line %zu is %lld, exceeds limit 10000",
                i+1, total_chars);
    }

    // Extract words: maximal runs of [A-Za-z-]
    vector<string> words;
    for (size_t i = 0; i < lines.size(); i++) {
        const string &s = lines[i];
        size_t n = s.size();
        size_t p = 0;
        while (p < n) {
            // Start of a word
            if ( (s[p] >= 'A' && s[p] <= 'Z')
              || (s[p] >= 'a' && s[p] <= 'z')
              || s[p] == '-' ) {
                size_t start = p;
                while (p < n && (
                       (s[p] >= 'A' && s[p] <= 'Z')
                     || (s[p] >= 'a' && s[p] <= 'z')
                     || s[p] == '-')) {
                    p++;
                }
                size_t len = p - start;
                // Extract the word
                string w = s.substr(start, len);
                // Check word length <= 100
                ensuref(len <= 100,
                        "Word length %zu at line %zu exceeds limit 100 (word: \"%s\")",
                        len, i+1, w.c_str());
                words.push_back(w);
            } else {
                p++;
            }
        }
    }

    // There must be at least one word (the E-N-D marker)
    ensuref(!words.empty(), "No words found in input");

    // Find the end marker "E-N-D"
    int end_idx = -1;
    for (int i = 0; i < (int)words.size(); i++) {
        if (words[i] == "E-N-D") {
            end_idx = i;
            break;
        }
    }
    ensuref(end_idx != -1,
            "Missing end marker \"E-N-D\"");

    // Ensure no words after the first E-N-D
    ensuref(end_idx == (int)words.size() - 1,
            "Found word \"%s\" after end marker \"E-N-D\" at word index %d",
            words[end_idx+1].c_str(), end_idx+1);

    // Finally, ensure we've consumed exactly all input
    inf.readEof();
    return 0;
}
