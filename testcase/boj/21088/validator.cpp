#include "testlib.h"

using namespace std;

// Helper function to check if a number has unnecessary leading zeros
bool has_leading_zeros(const string& s) {
    // "0" is allowed, but "00", "01", etc. are not
    return s.size() > 1 && s[0] == '0';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read the array as tokens, to check for leading zeros
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        string token = inf.readToken("[0-9]+", "a_i");
        ensuref(token.size() <= 18, "a[%d] has more than 18 digits", i+1);
        ensuref(!has_leading_zeros(token), "a[%d] has unnecessary leading zeros: '%s'", i+1, token.c_str());

        // Convert to long long and check bounds
        long long val = 0;
        for (char c : token) {
            val = val * 10 + (c - '0');
        }
        ensuref(val >= 1 && val <= 1000000000000000000LL, "a[%d] = %lld is out of bounds", i+1, val);
        a[i] = val;

        if (i + 1 < n) inf.readSpace();
        else inf.readEoln();
    }

    inf.readEof();
}
