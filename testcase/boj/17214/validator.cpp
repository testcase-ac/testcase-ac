#include "testlib.h"
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

// Helper to check if a string represents a valid integer (no leading zeros except "0")
bool isValidInt(const string& s, int minv, int maxv) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') {
        if (s.size() == 1) return false;
        start = 1;
    }
    // No leading zeros unless the number is exactly "0" or "-0"
    if (s[start] == '0' && s.size() > start+1) return false;
    // All digits
    for (int i = start; i < (int)s.size(); ++i)
        if (!isdigit(s[i])) return false;
    // Range check
    long long val = atoll(s.c_str());
    if (val < minv || val > maxv) return false;
    return true;
}

// Helper to parse a term and return (coefficient, degree), or fail
// Returns true if a term was parsed, false if not
// pos is updated to after the parsed term
bool parse_term(const string& s, int& pos, int& coeff, int& degree) {
    int n = s.size();
    int start = pos;
    int sign = 1;
    if (pos < n && (s[pos] == '+' || s[pos] == '-')) {
        if (s[pos] == '-') sign = -1;
        ++pos;
    }
    // Parse coefficient (possibly omitted)
    int coeff_start = pos;
    while (pos < n && isdigit(s[pos])) ++pos;
    string coeff_str = s.substr(coeff_start, pos - coeff_start);
    bool coeff_given = !coeff_str.empty();
    int c = 1;
    if (coeff_given) {
        // No leading zeros except "0"
        if (coeff_str.size() > 1 && coeff_str[0] == '0') return false;
        c = atoi(coeff_str.c_str());
    }
    // Now, check for variable part
    if (pos < n && s[pos] == 'x') {
        ++pos;
        // Degree 1 or 2
        if (pos < n && s[pos] == 'x') {
            ++pos;
            degree = 2;
        } else {
            degree = 1;
        }
        coeff = sign * c;
        // For degree 1 or 2, coefficient must be nonzero, abs <= 10000, and even
        if (abs(coeff) > 10000) return false;
        if (coeff == 0) return false;
        if (coeff % 2 != 0) return false;
        // If abs(coeff) == 1, coefficient must be omitted
        if (abs(coeff) == 1 && coeff_given) return false;
        // If abs(coeff) != 1, coefficient must be present and not omitted
        if (abs(coeff) != 1 && !coeff_given) return false;
        return true;
    } else {
        // Constant term
        degree = 0;
        // For constant, sign and coeff_str must be present
        if (!coeff_given) return false;
        coeff = sign * c;
        if (abs(coeff) > 10000) return false;
        return true;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[^]+", "polynomial");
    ensuref(!line.empty(), "Input line is empty");

    // Parse terms
    int pos = 0, n = line.size();
    int term_cnt = 0;
    int coeffs[3] = {0, 0, 0}; // degree 0, 1, 2
    bool degree_used[3] = {false, false, false};
    int last_degree = 3; // for order check

    while (pos < n) {
        // Parse term
        int coeff, degree;
        int term_start = pos;
        bool ok = parse_term(line, pos, coeff, degree);
        ensuref(ok, "Invalid term at position %d in input: '%s'", term_start, line.substr(term_start).c_str());
        ensuref(!degree_used[degree], "Duplicate degree %d term", degree);
        ensuref(degree < last_degree, "Terms not in decreasing degree order at position %d", term_start);
        last_degree = degree;
        degree_used[degree] = true;
        coeffs[degree] = coeff;
        ++term_cnt;
        // After term, expect + or - or end
        if (pos < n) {
            if (line[pos] == '+') ++pos;
            else if (line[pos] == '-') ; // handled in parse_term
            else ensuref(false, "Unexpected character '%c' at position %d", line[pos], pos);
        }
    }
    ensuref(term_cnt >= 1 && term_cnt <= 2, "Number of terms must be 1 or 2, got %d", term_cnt);

    inf.readEof();
}
