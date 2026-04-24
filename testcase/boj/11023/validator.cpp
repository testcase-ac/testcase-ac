#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line of numbers (no EOLN included)
    string line = inf.readLine("[^]+", "line");

    // Check that the line is not empty
    ensuref(!line.empty(), "Input line must not be empty");

    // Allowed characters: digits and spaces
    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];
        ensuref((c >= '0' && c <= '9') || c == ' ',
                "Invalid character '%c' at position %d: only digits and spaces allowed", c, i);
    }

    // No leading or trailing spaces
    ensuref(line.front() != ' ', "Leading space is not allowed");
    ensuref(line.back()  != ' ', "Trailing space is not allowed");

    // No consecutive spaces
    ensuref(line.find("  ") == string::npos,
            "Multiple consecutive spaces are not allowed");

    // Split by single spaces
    vector<string> tokens;
    {
        int n = (int)line.size();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && line[j] != ' ') j++;
            tokens.push_back(line.substr(i, j - i));
            i = j + 1; // skip the space
        }
    }

    // Number of tokens is N: must satisfy 1 ≤ N ≤ 100
    int N = (int)tokens.size();
    ensuref(1 <= N && N <= 100,
            "Number of integers N must satisfy 1 ≤ N ≤ 100, but found N = %d", N);

    // Validate each token
    for (int idx = 0; idx < N; idx++) {
        const string &tok = tokens[idx];
        // Token must be non-empty
        ensuref(!tok.empty(), "Empty token at index %d", idx);

        // No leading zero
        ensuref(tok[0] != '0',
                "Token at index %d must not start with '0' (no leading zeros), but got \"%s\"",
                idx, tok.c_str());

        // All characters must be digits
        for (int j = 0; j < (int)tok.size(); j++) {
            ensuref(isdigit(tok[j]),
                    "Non-digit character '%c' in token at index %d: \"%s\"",
                    tok[j], idx, tok.c_str());
        }

        // Length at most 5 digits (since max value is 10000)
        ensuref((int)tok.size() <= 5,
                "Token at index %d has too many digits (%d > 5): \"%s\"",
                idx, (int)tok.size(), tok.c_str());

        // Parse integer value
        int val = 0;
        for (char c : tok) {
            val = val * 10 + (c - '0');
        }

        // Each number must be a natural number 1..10000
        ensuref(1 <= val && val <= 10000,
                "Value at index %d must be in the range [1,10000], but got %d", idx, val);
    }

    // Ensure no extra input after the line
    inf.readEof();

    return 0;
}
