#include "testlib.h"
#include <string>
#include <cctype>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire conditional expression S
    string s = inf.readLine("[^]+", "S");
    int n = (int)s.size();
    // Length constraint
    ensuref(n >= 1 && n <= 1000000,
            "Length of S must be between 1 and 1e6, but got %d", n);
    // Check allowed characters only
    for (int i = 0; i < n; i++) {
        char c = s[i];
        bool ok = isalpha(c) || isdigit(c) || c=='-' || c=='=' || c=='!' || c=='&';
        ensuref(ok, "Invalid character '%c' at position %d", c, i);
    }

    int pos = 0;
    int expr_cnt = 0;
    while (pos < n) {
        // --- Parse first term (variable or integer) ---
        ensuref(pos < n, "Unexpected end at pos %d when parsing term1", pos);
        if (isalpha(s[pos])) {
            // variable: [a-zA-Z]+
            int st = pos;
            while (pos < n && isalpha(s[pos])) pos++;
            ensuref(pos > st, "Empty variable at pos %d", st);
        } else {
            // integer
            bool neg = false;
            if (s[pos] == '-') {
                neg = true;
                pos++;
                // "-0" is forbidden, and must have at least one digit after '-'
                ensuref(pos < n, "Minus without digits at pos %d", pos);
                ensuref(s[pos] != '0',
                        "Invalid integer '-0' or leading zero at pos %d", pos);
            }
            ensuref(pos < n && isdigit(s[pos]),
                    "Expected digit at pos %d, got '%c'", pos, pos < n ? s[pos] : '?');
            if (s[pos] == '0') {
                // only "0" is allowed
                ensuref(!neg, "Invalid integer '-0' at pos %d", pos);
                pos++;
            } else {
                // non-zero-starting integer
                ensuref(s[pos] >= '1' && s[pos] <= '9',
                        "Leading zero in integer at pos %d", pos);
                __int128 val = 0;
                while (pos < n && isdigit(s[pos])) {
                    val = val * 10 + (s[pos] - '0');
                    ensuref(val <= 1000000000,
                            "Absolute integer value exceeds 1e9 at pos %d", pos);
                    pos++;
                }
            }
        }

        // --- Parse operator "==" or "!=" ---
        ensuref(pos + 1 < n,
                "Operator missing or incomplete at pos %d", pos);
        if (!(s[pos] == '=' && s[pos+1] == '=')
         && !(s[pos] == '!' && s[pos+1] == '=')) {
            ensuref(false,
                    "Invalid operator '%c%c' at pos %d", 
                    s[pos], s[pos+1], pos);
        }
        pos += 2;

        // --- Parse second term ---
        ensuref(pos < n, "Unexpected end at pos %d when parsing term2", pos);
        if (isalpha(s[pos])) {
            int st = pos;
            while (pos < n && isalpha(s[pos])) pos++;
            ensuref(pos > st, "Empty variable at pos %d", st);
        } else {
            bool neg = false;
            if (s[pos] == '-') {
                neg = true;
                pos++;
                ensuref(pos < n, "Minus without digits at pos %d", pos);
                ensuref(s[pos] != '0',
                        "Invalid integer '-0' or leading zero at pos %d", pos);
            }
            ensuref(pos < n && isdigit(s[pos]),
                    "Expected digit at pos %d, got '%c'", pos, pos < n ? s[pos] : '?');
            if (s[pos] == '0') {
                ensuref(!neg, "Invalid integer '-0' at pos %d", pos);
                pos++;
            } else {
                ensuref(s[pos] >= '1' && s[pos] <= '9',
                        "Leading zero in integer at pos %d", pos);
                __int128 val = 0;
                while (pos < n && isdigit(s[pos])) {
                    val = val * 10 + (s[pos] - '0');
                    ensuref(val <= 1000000000,
                            "Absolute integer value exceeds 1e9 at pos %d", pos);
                    pos++;
                }
            }
        }

        expr_cnt++;
        // If at end, done; otherwise expect "&&"
        if (pos == n) break;
        ensuref(pos + 1 < n,
                "Expected '&&' at pos %d, but string ended", pos);
        ensuref(s[pos] == '&' && s[pos+1] == '&',
                "Expected '&&' at pos %d, got '%c%c'", 
                pos, s[pos], s[pos+1]);
        pos += 2;
    }

    ensuref(expr_cnt >= 1, "Expected at least one comparison, found %d", expr_cnt);
    inf.readEof();
    return 0;
}
