#include "testlib.h"

using namespace std;

bool is_valid_decimal(const string& s, int max_decimal_digits) {
    // Check if s is a valid decimal with at most max_decimal_digits after the decimal point
    // and no leading zeros unless s == "0" or s starts with "0."
    int n = s.size();
    if (n == 0) return false;
    int dot_pos = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '.') {
            if (dot_pos != -1) return false; // more than one dot
            dot_pos = i;
        } else if (!isdigit(s[i])) {
            return false;
        }
    }
    if (dot_pos == -1) {
        // integer
        if (s.size() > 1 && s[0] == '0') return false; // leading zeros
        return true;
    } else {
        // decimal
        if (dot_pos == 0) return false; // ".xx" not allowed
        if (dot_pos == n-1) return false; // "xx." not allowed
        if (dot_pos > 1 && s[0] == '0') return false; // leading zeros
        if (dot_pos == 1 && s[0] == '0') {
            // ok: "0.xxx"
        }
        int dec_digits = n - dot_pos - 1;
        if (dec_digits > max_decimal_digits) return false;
        return true;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read x
    string x_str = inf.readToken("[^ ]+", "x");
    ensuref(is_valid_decimal(x_str, 2), "x is not a valid decimal with at most 2 digits after decimal point and no leading zeros: '%s'", x_str.c_str());
    double x = atof(x_str.c_str());
    ensuref(x >= 0.0 && x < 100.0, "x = %s is out of range [0, 100)", x_str.c_str());

    inf.readSpace();

    // Read p
    string p_str = inf.readToken("[^ \n]+", "p");
    ensuref(is_valid_decimal(p_str, 2), "p is not a valid decimal with at most 2 digits after decimal point and no leading zeros: '%s'", p_str.c_str());
    double p = atof(p_str.c_str());
    ensuref(p >= 0.0 && p < 50.0, "p = %s is out of range [0, 50)", p_str.c_str());

    inf.readEoln();
    inf.readEof();
}
