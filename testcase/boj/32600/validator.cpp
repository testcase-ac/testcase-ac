#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

bool is_valid_prob(const string& s) {
    // Must be in decimal form, not scientific notation, exactly 3 digits after decimal
    // Acceptable: "0.000" to "1.000"
    // Not acceptable: "00.123", "1.00", "1.", "1.0000", "1e-3", "1.0", etc.
    // Acceptable: "0.123", "1.000"
    // Pattern: "0.ddd" or "1.000"
    if (s.size() != 5) return false;
    if (s[1] != '.' || !isdigit(s[0]) || !isdigit(s[2]) || !isdigit(s[3]) || !isdigit(s[4])) return false;
    if (s[0] == '0') {
        // "0.ddd"
        return true;
    } else if (s[0] == '1') {
        // "1.ddd" -- only "1.000" is allowed
        return s == "1.000";
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    // Read n probabilities, each with exactly 3 digits after decimal, decimal form, no scientific notation
    vector<double> p(n);
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[^ ]+", "p_i");
        ensuref(is_valid_prob(s), "p[%d] = \"%s\" is not a valid probability in decimal form with exactly 3 digits after decimal", i+1, s.c_str());
        // Convert to double for range check
        double val = atof(s.c_str());
        ensuref(val >= 0.0 && val <= 1.0, "p[%d] = \"%s\" is not in [0,1]", i+1, s.c_str());
        p[i] = val;
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    // Read m dependencies, check a != b, 1 <= a,b <= n, and no duplicate (a,b)
    set<pair<int, int>> deps;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();
        ensuref(a != b, "Dependency from a step to itself at line %d: (%d, %d)", i+3, a, b);
        ensuref(!deps.count({a, b}), "Duplicate dependency at line %d: (%d, %d)", i+3, a, b);
        deps.insert({a, b});
    }

    inf.readEof();
}
