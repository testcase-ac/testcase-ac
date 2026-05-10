#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool is_digits(const string& s) {
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 600, "n");
    inf.readEoln();

    // Read a_i as tokens (to check for leading zeros)
    vector<string> a_strs;
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[^ ]+", "a_i");
        // Check: only digits
        ensuref(is_digits(s), "a_%d is not a valid integer: '%s'", i+1, s.c_str());
        // Check: no leading zeros
        ensuref(s.size() == 1 || s[0] != '0', "a_%d has leading zeros: '%s'", i+1, s.c_str());
        // Check: in [2, 10^18]
        ensuref(s.size() <= 18, "a_%d is too large: '%s'", i+1, s.c_str());
        if (s.size() == 18) {
            // 10^18 = 1000000000000000000
            ensuref(s <= "1000000000000000000", "a_%d exceeds 10^18: '%s'", i+1, s.c_str());
        }
        ensuref(!(s.size() > 1 && s[0] == '0'), "a_%d has unnecessary leading zeros: '%s'", i+1, s.c_str());
        // Check: at least 2
        if (s.size() < 18) {
            long long val = 0;
            for (char c : s) val = val * 10 + (c - '0');
            ensuref(val >= 2, "a_%d is less than 2: '%s'", i+1, s.c_str());
        } else {
            ensuref(s >= "000000000000000002", "a_%d is less than 2: '%s'", i+1, s.c_str());
        }
        a_strs.push_back(s);
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    inf.readEof();
}
