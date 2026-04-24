#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read all lines of S until EOF
    vector<string> lines;
    // There must be at least one line
    // We read lines until EOF. Each line must be non-empty and only digits and commas.
    // Use eof() to detect end.
    while (!inf.eof()) {
        // Read a line of one or more characters from [0-9,]
        string line = inf.readLine("[0-9,]+", "S_line");
        lines.push_back(line);
    }
    // After reading lines, we should be exactly at EOF
    // But we'll do final readEof() at end.

    ensuref(!lines.empty(), "Input must contain at least one line");

    // Concatenate lines to form S
    int total_len = 0;
    for (int i = 0; i < (int)lines.size(); i++) {
        total_len += (int)lines[i].size();
    }
    ensuref(total_len <= 10000,
            "Total length of S exceeds 10000: %d", total_len);

    string S;
    S.reserve(total_len);
    for (auto &ln : lines) {
        S += ln;
    }

    // Check first and last characters are digits
    ensuref(!S.empty(), "Concatenated string S is empty");
    ensuref(isdigit(S.front()),
            "First character of S is not a digit: '%c'", S.front());
    ensuref(isdigit(S.back()),
            "Last character of S is not a digit: '%c'", S.back());

    // Check no consecutive commas and all chars are valid
    for (int i = 0; i < (int)S.size(); i++) {
        char c = S[i];
        ensuref(c == ',' || isdigit(c),
                "Invalid character in S at position %d: '%c'", i, c);
        if (i > 0 && S[i] == ',' && S[i-1] == ',') {
            ensuref(false,
                    "Consecutive commas in S at positions %d and %d", i-1, i);
        }
    }

    // Split by commas and validate each number
    vector<string> tokens;
    {
        int n = S.size();
        int start = 0;
        for (int i = 0; i <= n; i++) {
            if (i == n || S[i] == ',') {
                int len = i - start;
                ensuref(len > 0,
                        "Empty number segment at positions %d-%d", start, i-1);
                tokens.push_back(S.substr(start, len));
                start = i + 1;
            }
        }
    }
    ensuref(!tokens.empty(), "No numbers found in S");

    // For each token, parse to integer and check 1 <= x <= 1e6
    for (int idx = 0; idx < (int)tokens.size(); idx++) {
        const string &t = tokens[idx];
        // Parse safely with __int128
        __int128 val = 0;
        for (char c : t) {
            // we already know c is digit
            val = val * 10 + (c - '0');
            // early bound check
            ensuref(val <= (__int128)1000000,
                    "Number too large in segment %d: \"%s\" > 1000000",
                    idx, t.c_str());
        }
        ensuref(val >= 1,
                "Number not positive in segment %d: \"%s\"", idx, t.c_str());
    }

    // Ensure exactly one newline at EOF
    inf.readEof();
    return 0;
}
