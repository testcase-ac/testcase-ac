#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We read lines one by one: each line must be exactly a token (no spaces), then EOLN.
    // The sequence ends with a line "999". Before that, there must be at least two measurements.
    int meas_count = 0;
    while (true) {
        // Read the entire line (excluding the EOLN)
        string line = inf.readLine("[^]+", "line");
        // The line must not contain any whitespace
        ensuref(!line.empty(), "Empty line is not allowed");
        for (int i = 0; i < (int)line.size(); i++) {
            char c = line[i];
            ensuref(!isspace(c), "Whitespace character found in line \"%s\"", line.c_str());
        }
        // Check for sentinel
        if (line == "999") {
            // End of input
            break;
        }
        // Validate the format: optional '-', then digits, optional '.' and 1 or 2 digits
        const string &s = line;
        int n = s.size();
        int pos = 0;
        bool neg = false;
        if (s[pos] == '-') {
            neg = true;
            pos++;
            ensuref(pos < n, "No digits after '-' in \"%s\"", s.c_str());
        }
        // There must be at least one digit in the integer part
        ensuref(pos < n && isdigit(s[pos]), "Expected digit at position %d in \"%s\"", pos, s.c_str());
        // Parse integer part
        __int128 ip = 0;
        int int_digits = 0;
        while (pos < n && isdigit(s[pos])) {
            int digit = s[pos] - '0';
            // Prevent ip overflow roughly
            ensuref(ip <= (__int128(1e30)), "Integer part too large in \"%s\"", s.c_str());
            ip = ip * 10 + digit;
            pos++;
            int_digits++;
        }
        ensuref(int_digits >= 1, "No integer digits found in \"%s\"", s.c_str());
        // Parse fractional part if any
        __int128 frac = 0;
        int frac_digits = 0;
        if (pos < n) {
            ensuref(s[pos] == '.', "Unexpected character '%c' at position %d in \"%s\"", s[pos], pos, s.c_str());
            pos++;
            ensuref(pos < n && isdigit(s[pos]), "No digits after decimal point in \"%s\"", s.c_str());
            while (pos < n && isdigit(s[pos])) {
                int digit = s[pos] - '0';
                if (frac_digits < 2) {
                    frac = frac * 10 + digit;
                }
                frac_digits++;
                pos++;
            }
            ensuref(frac_digits >= 1 && frac_digits <= 2,
                    "Fractional part must have 1 or 2 digits in \"%s\"", s.c_str());
        }
        // Entire string must be consumed
        ensuref(pos == n, "Extra characters after valid number in \"%s\"", s.c_str());
        // Convert to hundredths
        __int128 val100 = ip * 100;
        if (frac_digits == 1) {
            frac *= 10;
        }
        // if frac_digits == 0, frac is already 0; if ==2, use as is
        val100 += frac;
        if (neg) val100 = -val100;
        // Check numeric range: [-10.00, 200.00] => [-1000, 20000] in hundredths
        ensuref(val100 >= -1000 && val100 <= 20000,
                "Temperature %.2f out of allowed range [-10.00,200.00] in \"%s\"",
                double(val100) / 100.0, s.c_str());
        meas_count++;
    }
    // Must have at least two measurements before sentinel
    ensuref(meas_count >= 2,
            "At least two measurements are required, but only %d provided", meas_count);

    // No extra content after sentinel newline
    inf.readEof();
    return 0;
}
