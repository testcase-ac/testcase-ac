#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire line of input (must have at least one character)
    string line = inf.readLine("[^]+", "line");

    // No leading or trailing spaces
    ensuref(!line.empty(), "Input line is empty");
    ensuref(line.front() != ' ', "Line starts with a space");
    ensuref(line.back()  != ' ', "Line ends with a space");
    // No consecutive spaces
    ensuref(line.find("  ") == string::npos, "Multiple consecutive spaces are not allowed");

    // Ensure only digits, minus signs, and spaces appear
    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];
        ensuref(c == ' ' || c == '-' || (c >= '0' && c <= '9'),
                "Invalid character '%c' at position %d", c, i+1);
    }

    // Parse tokens one by one, checking format and range
    int len = (int)line.size();
    int i = 0;
    int token_count = 0;
    while (i < len) {
        token_count++;
        int token_idx = token_count;

        // Optional minus
        bool neg = false;
        if (line[i] == '-') {
            neg = true;
            i++;
            ensuref(i < len && isdigit(line[i]),
                    "Token %d: '-' not followed by digits", token_idx);
        }
        // Must have at least one digit
        ensuref(i < len && isdigit(line[i]),
                "Token %d: token does not start with digit or minus", token_idx);

        // Parse digits
        __int128 val = 0;
        bool too_large = false;
        while (i < len && isdigit(line[i])) {
            int d = line[i] - '0';
            if (!too_large) {
                val = val * 10 + d;
                if (val > 1000000) {
                    too_large = true;
                }
            }
            i++;
        }

        long long finalVal = neg ? -(long long)val : (long long)val;
        ensuref(!too_large && finalVal >= -1000000LL && finalVal <= 1000000LL,
                "Token %d: value %s%lld is out of range [-1000000,1000000]",
                token_idx, neg ? "-" : "", (long long)val);

        // If not at end, the next character must be a single space
        if (i < len) {
            ensuref(line[i] == ' ',
                    "Invalid character '%c' at position %d, expected space",
                    line[i], i+1);
            i++;
        }
    }

    // Check number of tokens
    ensuref(token_count >= 1 && token_count <= 1000000,
            "Number of integers N = %d is out of range [1,1000000]",
            token_count);

    // No more input after this line
    inf.readEof();
    return 0;
}
