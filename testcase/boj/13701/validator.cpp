#include "testlib.h"
#include <string>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line of input (all tokens until EOL)
    string line = inf.readLine("[^]+", "line");

    // Line must not be empty
    ensuref(!line.empty(), "Input line is empty");

    // No leading or trailing spaces
    ensuref(line.front() != ' ', "Leading space detected in the input line");
    ensuref(line.back()  != ' ', "Trailing space detected in the input line");

    // No consecutive spaces
    ensuref(line.find("  ") == string::npos, "Consecutive spaces detected in the input line");

    // Constants
    const int MAX_TOKENS = 5000000;
    const int64_t MAX_VAL = 1LL << 25; // 2^25

    // Scan the line character by character, parsing integers on the fly
    int token_len = 0;       // length of the current token in digits
    int token_count = 0;     // number of tokens seen
    int val = 0;             // current token value

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == ' ') {
            // We must have just finished a token
            ensuref(token_len > 0,
                    "Empty token encountered before space at byte position %d", int(i));
            // Reset for the next token
            token_len = 0;
            val = 0;
        } else if (c >= '0' && c <= '9') {
            // Digit: either start of a new token or continuation
            if (token_len == 0) {
                // Starting a new token
                token_count++;
                ensuref(token_count <= MAX_TOKENS,
                        "Number of integers N = %d exceeds the maximum %d",
                        token_count, MAX_TOKENS);
            }
            token_len++;
            // Token length must be reasonable (max 8 digits for < 2^25)
            ensuref(token_len <= 8,
                    "Token too long (more than 8 digits) ending at byte position %d", int(i));
            // Accumulate value and check bound
            val = val * 10 + (c - '0');
            ensuref(val < MAX_VAL,
                    "Value %d parsed so far at byte position %d is >= 2^25", val, int(i));
        } else {
            // Invalid character (tabs, letters, etc.)
            ensuref(false,
                    "Invalid character '%c' at byte position %d; only digits and spaces allowed",
                    c, int(i));
        }
    }

    // After the loop, we must have ended inside a token
    ensuref(token_len > 0, "Input line must end with a digit, not a space");

    // Check total number of tokens
    ensuref(token_count >= 1 && token_count <= MAX_TOKENS,
            "Number of integers N = %d is out of allowed range [1, %d]",
            token_count, MAX_TOKENS);

    // No further input allowed
    inf.readEof();
    return 0;
}
