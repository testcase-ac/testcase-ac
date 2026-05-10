#include "testlib.h"
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// Checks if s is a valid positive integer (no leading zeros except "0")
bool is_valid_positive_integer(const string& s) {
    if (s.empty()) return false;
    if (s.size() > 1 && s[0] == '0') return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

// Checks if s is in [1, 10^12]
bool is_in_range(const string& s) {
    if (s.size() > 13) return false; // 10^12 is 13 digits at most
    if (s.size() < 13) return true;
    // s.size() == 13
    // 10^12 = 1000000000000
    return s <= "1000000000000";
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the first line (may contain n and some elements)
    string first_line = inf.readLine("[^]+", "first line");
    stringstream ss(first_line);

    string token;
    // Read n
    bool ok = static_cast<bool>(ss >> token);
    ensuref(ok, "First line must contain at least n");
    ensuref(is_valid_positive_integer(token), "n is not a valid positive integer: '%s'", token.c_str());
    ensuref(is_in_range(token), "n is out of range: '%s'", token.c_str());
    long long n = stoll(token);
    ensuref(1LL <= n && n <= 1000000LL, "n must be in [1, 10^6], got %lld", n);

    long long cnt = 0;
    // Read any elements on the first line after n
    while (ss >> token) {
        ensuref(is_valid_positive_integer(token), 
            "Element #%lld: not a valid positive integer: '%s'", cnt+1, token.c_str());
        ensuref(is_in_range(token), 
            "Element #%lld: value '%s' exceeds 10^12", cnt+1, token.c_str());
        ensuref(token != "0", 
            "Element #%lld: value is zero, must be strictly positive", cnt+1);
        ++cnt;
        ensuref(cnt <= n, 
            "Too many elements: expected %lld, got at least %lld", n, cnt);
    }

    // Now read lines until we have n elements
    while (cnt < n) {
        string line = inf.readLine("[^]*", "input line");
        stringstream ss2(line);
        while (ss2 >> token) {
            ensuref(is_valid_positive_integer(token), 
                "Element #%lld: not a valid positive integer: '%s'", cnt+1, token.c_str());
            ensuref(is_in_range(token), 
                "Element #%lld: value '%s' exceeds 10^12", cnt+1, token.c_str());
            ensuref(token != "0", 
                "Element #%lld: value is zero, must be strictly positive", cnt+1);
            ++cnt;
            ensuref(cnt <= n, 
                "Too many elements: expected %lld, got at least %lld", n, cnt);
        }
    }
    ensuref(cnt == n, "Number of elements read (%lld) does not match n (%lld)", cnt, n);

    // After reading n elements, there should be no more non-empty lines or tokens
    // Ensure whitespace strictness: no extra lines, no extra tokens, no trailing spaces
    // Try to read another line; if it exists and is not empty or whitespace, error
    // But testlib requires strict EOF after last line

    inf.readEof();
}
