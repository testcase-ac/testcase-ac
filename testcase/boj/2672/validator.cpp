#include "testlib.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Helper function to check if a string is a valid real number with at most 1 decimal place, no leading zeros except "0.x"
bool is_valid_real(const string& s) {
    // Acceptable: "0", "0.0", "12", "12.3", "999.9", "1000.0"
    // Not acceptable: "01", "00.1", "1.23", "1.", ".1", "1.234", "1.10"
    int n = s.size();
    if (n == 0) return false;
    int dot = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '.') {
            if (dot != -1) return false; // multiple dots
            dot = i;
        } else if (!isdigit(s[i])) {
            return false;
        }
    }
    if (dot == -1) {
        // No dot, must be integer
        if (n > 1 && s[0] == '0') return false; // leading zero
        return true;
    } else {
        // Dot present
        if (dot == 0) return false; // ".x" not allowed
        if (dot == n-1) return false; // "x." not allowed
        // Check integer part
        if (dot > 1 && s[0] == '0') return false; // leading zero in integer part
        // Check decimal part
        int dec_len = n - dot - 1;
        if (dec_len < 1 || dec_len > 1) return false; // must be exactly 1 decimal
        return true;
    }
}

double parse_real(const string& s) {
    // We already checked format, so safe to use stod
    return stod(s);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read 4 tokens (not numbers yet)
        string sx = inf.readToken("[^ ]+", "x");
        inf.readSpace();
        string sy = inf.readToken("[^ ]+", "y");
        inf.readSpace();
        string sw = inf.readToken("[^ ]+", "w");
        inf.readSpace();
        string sh = inf.readToken("[^ \n]+", "h");
        inf.readEoln();

        ensuref(is_valid_real(sx), "Invalid format for x at rectangle %d: '%s'", i+1, sx.c_str());
        ensuref(is_valid_real(sy), "Invalid format for y at rectangle %d: '%s'", i+1, sy.c_str());
        ensuref(is_valid_real(sw), "Invalid format for width at rectangle %d: '%s'", i+1, sw.c_str());
        ensuref(is_valid_real(sh), "Invalid format for height at rectangle %d: '%s'", i+1, sh.c_str());

        double x = parse_real(sx);
        double y = parse_real(sy);
        double w = parse_real(sw);
        double h = parse_real(sh);

        ensuref(x >= 0.0 && x <= 1000.0, "x out of range at rectangle %d: %s", i+1, sx.c_str());
        ensuref(y >= 0.0 && y <= 1000.0, "y out of range at rectangle %d: %s", i+1, sy.c_str());
        ensuref(w > 0.0 && w <= 1000.0, "width out of range at rectangle %d: %s", i+1, sw.c_str());
        ensuref(h > 0.0 && h <= 1000.0, "height out of range at rectangle %d: %s", i+1, sh.c_str());
        // No further geometric checks required by statement
    }

    inf.readEof();
}
