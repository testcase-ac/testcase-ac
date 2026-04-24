#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students
    long long N = inf.readLong(8LL, 10000000LL, "N");
    inf.readEoln();

    // Each of the next N lines: a score in [0.000,100.000] with 0.001 resolution,
    // formatted as integer part . exactly 3 digits fractional part.
    for (long long i = 0; i < N; i++) {
        // Read as a token matching digits+"."+3 digits
        string s = inf.readToken("[0-9]+\\.[0-9]{3}", "score");
        inf.readEoln();

        // Split into integer and fractional parts
        size_t dot = s.find('.');
        ensuref(dot != string::npos, "Internal error: no '.' in score '%s'", s.c_str());
        string ip = s.substr(0, dot);
        string fp = s.substr(dot + 1);

        // No leading zeros in integer part except for "0"
        ensuref(!((int)ip.size() > 1 && ip[0] == '0'),
                "Leading zero in integer part of score '%s'", s.c_str());

        // Parse integer part
        int ipart = 0;
        for (char c : ip) {
            ensuref(isdigit(c), "Non-digit '%c' in integer part of score '%s'", c, s.c_str());
            ipart = ipart * 10 + (c - '0');
            ensuref(ipart <= 100, "Integer part %d out of range in score '%s'", ipart, s.c_str());
        }
        ensuref(0 <= ipart && ipart <= 100,
                "Integer part %d out of range in score '%s'", ipart, s.c_str());

        // Parse fractional part
        int fpart = 0;
        for (char c : fp) {
            ensuref(isdigit(c), "Non-digit '%c' in fractional part of score '%s'", c, s.c_str());
            fpart = fpart * 10 + (c - '0');
        }
        // fp has exactly 3 digits by regex, so 0 <= fpart <= 999
        ensuref(0 <= fpart && fpart <= 999,
                "Fractional part %d out of range in score '%s'", fpart, s.c_str());

        // If integer part is 100, fractional must be 000
        if (ipart == 100) {
            ensuref(fpart == 0,
                    "Score '%s' invalid: if integer part is 100, fractional must be .000", s.c_str());
        }

        // Total in [0, 100000]
        int total = ipart * 1000 + fpart;
        ensuref(0 <= total && total <= 100000,
                "Computed score %d out of valid range [0,100000] for '%s'", total, s.c_str());
    }

    inf.readEof();
    return 0;
}
