#include "testlib.h"

#include <cmath>
#include <string>

using namespace std;

static bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

static long double read_real_token(const char* name, long double min_value, long double max_value) {
    string s = inf.readToken("[^ ]+", name);

    int i = 0;
    const int n = (int)s.size();
    bool has_minus = false;
    if (i < n && s[i] == '-') {
        has_minus = true;
        ++i;
    }

    ensuref(i < n && is_digit(s[i]), "%s must have an integer part", name);

    if (s[i] == '0') {
        ++i;
        ensuref(i == n || s[i] == '.', "%s must not have leading zeroes: %s", name, s.c_str());
    } else {
        while (i < n && is_digit(s[i])) {
            ++i;
        }
    }

    int frac_len = 0;
    if (i < n && s[i] == '.') {
        ++i;
        while (i < n && is_digit(s[i])) {
            ++i;
            ++frac_len;
        }
        ensuref(frac_len >= 1, "%s has a decimal point without fractional digits", name);
        ensuref(frac_len <= 8, "%s has more than 8 digits after the decimal point", name);
    }

    ensuref(i == n, "%s has invalid numeric format: %s", name, s.c_str());

    long double value = stold(s);
    ensuref(!has_minus || value < 0.0L, "%s has a minus sign but is not negative: %s", name, s.c_str());
    ensuref(min_value <= value && value <= max_value,
            "%s=%Lf is outside [%Lf, %Lf]",
            name,
            value,
            min_value,
            max_value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    const long double pi = acosl(-1.0L);
    const long double two_pi = 2.0L * pi;

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int system = inf.readInt(1, 2, "coordinate_system");
        inf.readEoln();

        if (system == 1) {
            read_real_token("x", -100.0L, 100.0L);
            inf.readSpace();
            read_real_token("y", -100.0L, 100.0L);
            inf.readEoln();
        } else {
            long double r = read_real_token("r", 0.0L, 100.0L);
            inf.readSpace();
            long double theta = read_real_token("theta", 0.0L, two_pi);
            inf.readEoln();

            ensuref(theta < two_pi, "theta must be less than 2*pi");
            ensuref(r != 0.0L || theta == 0.0L, "theta must be 0 when r is 0");
        }
    }

    inf.readEof();
}
