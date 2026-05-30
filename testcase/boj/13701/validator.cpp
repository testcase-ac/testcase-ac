#include "testlib.h"
#include <string>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[^]+", "numbers");

    ensuref(!line.empty(), "Input line is empty");
    ensuref(line.front() != ' ', "Leading space detected in the input line");
    ensuref(line.back() != ' ', "Trailing space detected in the input line");

    const int MAX_TOKENS = 5000000;
    const int64_t MAX_VAL = 1LL << 25; // 2^25

    int token_len = 0;       // length of the current token in digits
    int token_count = 0;     // number of tokens seen
    int val = 0;             // current token value
    bool leading_zero = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == ' ') {
            ensuref(token_len > 0,
                    "Empty token encountered before space at byte position %d", int(i));
            ensuref(!leading_zero || token_len == 1,
                    "Non-canonical integer with leading zero before byte position %d", int(i));
            token_len = 0;
            val = 0;
            leading_zero = false;
        } else if (c >= '0' && c <= '9') {
            if (token_len == 0) {
                token_count++;
                ensuref(token_count <= MAX_TOKENS,
                        "Number of integers N = %d exceeds the maximum %d",
                        token_count, MAX_TOKENS);
                leading_zero = (c == '0');
            }
            token_len++;
            ensuref(token_len <= 8,
                    "Token too long (more than 8 digits) ending at byte position %d", int(i));
            val = val * 10 + (c - '0');
            ensuref(val < MAX_VAL,
                    "Value %d parsed so far at byte position %d is >= 2^25", val, int(i));
        } else {
            ensuref(false,
                    "Invalid character '%c' at byte position %d; only digits and spaces allowed",
                    c, int(i));
        }
    }

    ensuref(token_len > 0, "Input line must end with a digit, not a space");
    ensuref(!leading_zero || token_len == 1,
            "Non-canonical integer with leading zero at end of line");

    ensuref(token_count >= 1 && token_count <= MAX_TOKENS,
            "Number of integers N = %d is out of allowed range [1, %d]",
            token_count, MAX_TOKENS);

    inf.readEof();
    return 0;
}
