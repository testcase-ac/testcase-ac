#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
#include <cassert>
using namespace std;

static int64_t parseInt(const string &t) {
    // Precondition: t is non-empty
    // Check sign and digits
    int n = (int)t.size();
    bool neg = false;
    int i = 0;
    if (t[0] == '-') {
        neg = true;
        i = 1;
        ensuref(n > 1, "Invalid integer representation: '%s'", t.c_str());
    }
    // Must have at least one digit
    ensuref(i < n, "Invalid integer representation: '%s'", t.c_str());
    // No leading zeros unless the number is exactly "0"
    if (i < n) {
        if (t[i] == '0' && i+1 < n) {
            ensuref(false, "Leading zero in integer: '%s'", t.c_str());
        }
    }
    // All remaining must be digits
    for (int j = i; j < n; j++) {
        ensuref(isdigit(t[j]), "Non-digit character in integer: '%s'", t.c_str());
    }
    // Parse to int64
    // Also guard against extremely long strings
    ensuref(n - (neg ? 1 : 0) <= 10, "Integer too long: '%s'", t.c_str());
    int64_t val = 0;
    for (int j = i; j < n; j++) {
        val = val * 10 + (t[j] - '0');
    }
    if (neg) val = -val;
    // Constraint abs(val) < 1e9
    ensuref(val > -1000000000LL && val < 1000000000LL,
            "Integer out of bounds [-1e9+1,1e9-1]: %lld from '%s'",
            (long long)val, t.c_str());
    return val;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read exactly one token (no spaces) and one newline, then EOF.
    string s = inf.readToken("[^]+", "range_str");
    inf.readEoln();

    // Check allowed characters
    for (char c : s) {
        bool ok = false;
        if (isdigit(c)) ok = true;
        else if (c == '(' || c == ')' || c == ',' || c == '-') ok = true;
        else {
            // only letters a,e,g,n,r allowed
            if (c=='a' || c=='e' || c=='g' || c=='n' || c=='r')
                ok = true;
        }
        ensuref(ok, "Illegal character '%c' in input", c);
    }

    // Must start with "range("
    const string pref = "range(";
    ensuref(s.size() > pref.size(), "Input too short");
    ensuref(s.substr(0, pref.size()) == pref, "Input must start with 'range('");
    // Must end with ')'
    ensuref(s.back() == ')', "Input must end with ')'");

    // Extract inside content
    string inside = s.substr(pref.size(), s.size() - pref.size() - 1);
    // Split by commas
    vector<string> parts;
    {
        size_t start = 0;
        while (start <= inside.size()) {
            size_t pos = inside.find(',', start);
            if (pos == string::npos) pos = inside.size();
            string part = inside.substr(start, pos - start);
            parts.push_back(part);
            start = pos + 1;
        }
    }
    // Must have 1,2,or 3 arguments
    ensuref(parts.size() >= 1 && parts.size() <= 3,
            "Number of arguments must be 1,2 or 3, got %d", (int)parts.size());

    // Parse each argument as integer
    vector<int64_t> vals;
    for (int i = 0; i < (int)parts.size(); i++) {
        const string &t = parts[i];
        // Non-empty
        ensuref(!t.empty(), "Empty argument %d", i+1);
        int64_t v = parseInt(t);
        vals.push_back(v);
    }
    // If three args, ensure d != 0
    if ((int)vals.size() == 3) {
        ensuref(vals[2] != 0, "Third argument (step) must be non-zero, got 0");
    }
    // All checks done
    inf.readEof();
    return 0;
}
