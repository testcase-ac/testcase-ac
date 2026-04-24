#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line S: only digits and commas
    string S = inf.readLine("[0-9,]+", "S");

    // Constraint: length between 1 and 100
    ensuref(!S.empty(), "S must be non-empty");
    ensuref((int)S.size() <= 100, "Length of S exceeds 100: %d", (int)S.size());

    // First and last character must be digit
    ensuref(isdigit(S.front()), "First character of S is not a digit: '%c'", S.front());
    ensuref(isdigit(S.back()), "Last character of S is not a digit: '%c'", S.back());

    // No consecutive commas
    for (int i = 0; i + 1 < (int)S.size(); i++) {
        if (S[i] == ',') {
            ensuref(S[i+1] != ',', "Consecutive commas detected at positions %d and %d", i, i+1);
        }
    }

    // Split by commas and validate each number
    vector<string> parts;
    {
        string cur;
        for (char c : S) {
            if (c == ',') {
                parts.push_back(cur);
                cur.clear();
            } else {
                cur.push_back(c);
            }
        }
        parts.push_back(cur);
    }

    // Each part must represent a natural number in [1, 1e6]
    for (int i = 0; i < (int)parts.size(); i++) {
        const string &num = parts[i];
        // should never be empty, but just in case
        ensuref(!num.empty(), "Empty number substring at index %d", i);
        // length: at most 7 digits (since 1e6 has 7 digits)
        ensuref((int)num.size() <= 7,
                "Number at index %d has too many digits (%d > 7): \"%s\"",
                i, (int)num.size(), num.c_str());
        // parse value
        int value = 0;
        for (char d : num) {
            ensuref(isdigit(d),
                    "Non-digit character '%c' in number at index %d: \"%s\"",
                    d, i, num.c_str());
            value = value * 10 + (d - '0');
            // we can check overflow guard here (value <= 1e6)
            ensuref(value <= 1000000,
                    "Value of number at index %d exceeds 1e6: %d", i, value);
        }
        // must be at least 1
        ensuref(value >= 1,
                "Value of number at index %d is less than 1: %d", i, value);
    }

    // End of file checks
    inf.readEof();
    return 0;
}
