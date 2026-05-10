#include "testlib.h"

using namespace std;

// Helper function to check if a string is a palindrome
bool is_palindrome(const string& s) {
    int n = int(s.size());
    for (int i = 0; i < n / 2; ++i)
        if (s[i] != s[n - 1 - i])
            return false;
    return true;
}

// Helper function to get binary representation without leading zeros
string to_binary(int x) {
    string s;
    while (x > 0) {
        s += char('0' + (x & 1));
        x >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

// For a given X, find the minimal number of +1/-1 operations to reach a number whose binary is palindrome
int min_ops_to_binary_palindrome(int x) {
    // Since X can be up to 1e9, and the minimal palindrome is always within a reasonable range,
    // we can check all numbers in [x-d, x+d] for increasing d, until we find a palindrome.
    // Since 1 <= X <= 1e9, and binary palindromes are relatively dense, d up to 100 is enough.
    // But to be safe, let's go up to d = 1e6.
    const int MAX_D = 1000000;
    for (int d = 0; d <= MAX_D; ++d) {
        // Check x-d if x-d >= 1
        if (x - d >= 1) {
            if (is_palindrome(to_binary(x - d)))
                return d;
        }
        // Check x+d (avoid d=0 double check)
        if (d > 0 && x + d <= 1000000000) {
            if (is_palindrome(to_binary(x + d)))
                return d;
        }
    }
    // Should never reach here for the given constraints
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        int X = inf.readInt(1, 1000000000, "X");
        inf.readEoln();

        // No leading zeros allowed in integer input, testlib's readInt already enforces this.

        // Validate that for this X, there exists at least one number reachable by allowed operations
        // whose binary representation is a palindrome.
        // The problem says: "For the given input, the answer always exists."
        // So we must check that for each X, there is at least one such number.
        int min_ops = min_ops_to_binary_palindrome(X);
        ensuref(min_ops != -1, "No reachable binary palindrome for X=%d", X);
    }

    inf.readEof();
}
