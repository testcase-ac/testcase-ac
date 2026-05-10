#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single token X
    string s = inf.readToken("[^]+", "X");
    inf.readEoln();

    // The converted decimal value must be in [1, 1'000'000]
    const long long MAXV = 1000000;

    // Helper to report overflow/invalid value
    auto check_range = [&](const __int128 &v, const string &orig){
        ensuref(v >= 1 && v <= MAXV,
                "Numeric value of input '%s' must be between 1 and %lld, but got %lld",
                orig.c_str(), MAXV, (long long)v);
    };

    if (s.size() >= 2 && s[0] == '0' && s[1] == 'x') {
        // Hexadecimal case
        ensuref(s.size() >= 3,
                "Hexadecimal input must have at least one digit after '0x', but got '%s'",
                s.c_str());
        __int128 val = 0;
        for (int i = 2; i < (int)s.size(); i++) {
            char c = s[i];
            ensuref((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'),
                    "Invalid hexadecimal digit '%c' in input '%s'", c, s.c_str());
            int d = (c <= '9' ? c - '0' : c - 'a' + 10);
            val = val * 16 + d;
            ensuref(val <= MAXV,
                    "Value of hexadecimal input '%s' exceeds maximum allowed (%lld): got %lld",
                    s.c_str(), MAXV, (long long)val);
        }
        check_range(val, s);

    } else if (s.size() >= 1 && s[0] == '0') {
        // Octal case
        ensuref(s.size() >= 2,
                "Octal input must have at least one digit after leading '0', but got '%s'",
                s.c_str());
        __int128 val = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            char c = s[i];
            ensuref(c >= '0' && c <= '7',
                    "Invalid octal digit '%c' in input '%s'", c, s.c_str());
            int d = c - '0';
            val = val * 8 + d;
            ensuref(val <= MAXV,
                    "Value of octal input '%s' exceeds maximum allowed (%lld): got %lld",
                    s.c_str(), MAXV, (long long)val);
        }
        check_range(val, s);

    } else {
        // Decimal case
        // Must consist solely of digits
        ensuref(!s.empty(), "Input string is empty");
        for (char c : s) {
            ensuref(c >= '0' && c <= '9',
                    "Invalid character '%c' in decimal input '%s'", c, s.c_str());
        }
        // Leading zero is not allowed in decimal (would be octal)
        ensuref(s[0] != '0',
                "Decimal input must not start with '0' (would be octal), but got '%s'",
                s.c_str());

        __int128 val = 0;
        for (char c : s) {
            int d = c - '0';
            val = val * 10 + d;
            ensuref(val <= MAXV,
                    "Value of decimal input '%s' exceeds maximum allowed (%lld): got %lld",
                    s.c_str(), MAXV, (long long)val);
        }
        check_range(val, s);
    }

    inf.readEof();
    return 0;
}
