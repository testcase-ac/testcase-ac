#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read the entire line (may contain spaces)
        string line = inf.readLine("[^]+", "expression");

        // No leading or trailing spaces
        ensuref(!line.empty(), "Line %d is empty", tc);
        ensuref(line.front() != ' ', "Line %d has leading space", tc);
        ensuref(line.back()  != ' ', "Line %d has trailing space", tc);

        // No consecutive spaces
        for (size_t i = 0; i + 1 < line.size(); i++) {
            ensuref(!(line[i] == ' ' && line[i+1] == ' '),
                    "Line %d has consecutive spaces at pos %d", tc, int(i));
        }

        // Split by spaces
        vector<string> tokens;
        size_t pos = 0;
        while (pos < line.size()) {
            size_t nxt = line.find(' ', pos);
            if (nxt == string::npos) {
                tokens.push_back(line.substr(pos));
                break;
            } else {
                tokens.push_back(line.substr(pos, nxt - pos));
                pos = nxt + 1;
            }
        }

        // Must have 1 (just a number) up to 4 tokens (number + up to 3 ops)
        ensuref(tokens.size() >= 1 && tokens.size() <= 4,
                "Line %d has invalid token count %d (must be 1 to 4)", tc, int(tokens.size()));

        // Validate the first token is a number: integer or one decimal place
        const string &num = tokens[0];
        int dotCount = 0;
        for (char c : num) if (c == '.') dotCount++;
        ensuref(dotCount <= 1, "Line %d: number '%s' has more than one dot", tc, num.c_str());

        // Parse integer and fractional parts
        long long intval = 0;
        int frac    = 0;  // digit 0..9
        if (dotCount == 0) {
            // All digits
            ensuref(!num.empty(), "Line %d: empty number token", tc);
            for (char c : num) {
                ensuref(isdigit(c), "Line %d: invalid character '%c' in integer '%s'",
                        tc, c, num.c_str());
                intval = intval * 10 + (c - '0');
            }
        } else {
            // Exactly one dot
            size_t p = num.find('.');
            ensuref(p != 0 && p + 1 < num.size(),
                    "Line %d: malformed decimal '%s'", tc, num.c_str());
            // integer part
            for (size_t i = 0; i < p; i++) {
                char c = num[i];
                ensuref(isdigit(c), "Line %d: invalid '%c' in integer part of '%s'",
                        tc, c, num.c_str());
                intval = intval * 10 + (c - '0');
            }
            // fractional part: exactly one digit after '.'
            ensuref(num.size() - p - 1 == 1,
                    "Line %d: decimal '%s' must have exactly one digit after decimal point",
                    tc, num.c_str());
            char fc = num[p+1];
            ensuref(isdigit(fc),
                    "Line %d: invalid '%c' in fractional part of '%s'",
                    tc, fc, num.c_str());
            frac = fc - '0';
        }
        // Check range 0.0 to 100.0 inclusive
        long long valueTimes10 = intval * 10 + frac;
        ensuref(0 <= valueTimes10 && valueTimes10 <= 1000,
                "Line %d: number '%s' out of range [0,100] (times10 = %lld)",
                tc, num.c_str(), valueTimes10);

        // Validate operators (tokens 1..end)
        for (size_t j = 1; j < tokens.size(); j++) {
            const string &op = tokens[j];
            ensuref(op.size() == 1,
                    "Line %d: operator token '%s' is not a single character", tc, op.c_str());
            char c = op[0];
            ensuref(c == '@' || c == '%' || c == '#',
                    "Line %d: invalid operator '%c' (only @, %, # allowed)", tc, c);
        }
    }

    inf.readEof();
    return 0;
}
