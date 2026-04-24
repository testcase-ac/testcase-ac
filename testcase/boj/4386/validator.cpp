#include "testlib.h"
#include <string>
#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;

static long double parse_and_check_coordinate(const string &s, int idx, char coord_name) {
    // Must contain at most one dot
    int dot_cnt = 0;
    for (char c : s) if (c == '.') dot_cnt++;
    ensuref(dot_cnt <= 1,
            "%c[%d] = \"%s\": too many decimal points (%d)", coord_name, idx, s.c_str(), dot_cnt);
    // Split integer and fractional part
    string ip, fp;
    auto pos = s.find('.');
    if (pos == string::npos) {
        ip = s;
    } else {
        ip = s.substr(0, pos);
        fp = s.substr(pos + 1);
    }
    // Integer part must be non-empty and all digits
    ensuref(!ip.empty(),
            "%c[%d] = \"%s\": missing integer part", coord_name, idx, s.c_str());
    for (char c : ip) {
        ensuref(isdigit(c),
                "%c[%d] = \"%s\": invalid character '%c' in integer part", coord_name, idx, s.c_str(), c);
    }
    // Fractional part if present: length 1 or 2, all digits
    if (dot_cnt == 1) {
        ensuref(fp.size() >= 1 && fp.size() <= 2,
                "%c[%d] = \"%s\": fractional part must have 1 or 2 digits, got %zu", 
                coord_name, idx, s.c_str(), fp.size());
        for (char c : fp) {
            ensuref(isdigit(c),
                    "%c[%d] = \"%s\": invalid character '%c' in fractional part", 
                    coord_name, idx, s.c_str(), c);
        }
    } else {
        // no dot, fp empty
    }
    // Convert to long double
    // stold will succeed since we validated format
    long double v = stold(s);
    // Must be >0 and <= 1000
    ensuref(v > 0.0L && v <= 1000.0L,
            "%c[%d] = %Lf is out of range (0, 1000]", coord_name, idx, v);
    return v;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of stars
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Read each star's coordinates
    for (int i = 0; i < n; i++) {
        // Read x as a token (no spaces)
        string xs = inf.readToken("[^ ]+", "x");
        inf.readSpace();
        // Read y
        string ys = inf.readToken("[^ ]+", "y");
        inf.readEoln();

        // Check format and range
        parse_and_check_coordinate(xs, i, 'x');
        parse_and_check_coordinate(ys, i, 'y');
    }

    // No extra content
    inf.readEof();
    return 0;
}
