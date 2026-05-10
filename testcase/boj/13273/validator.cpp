#include "testlib.h"
#include <string>
#include <set>
#include <vector>
#include <map>
using namespace std;

// Map of single roman numerals to their values
map<char, int> roman_single = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
};

// Map of subtractive pairs to their values
map<string, int> roman_subtractive = {
    {"IV", 4},
    {"IX", 9},
    {"XL", 40},
    {"XC", 90},
    {"CD", 400},
    {"CM", 900}
};

// All valid roman numerals in order, for greedy parsing
vector<pair<string, int>> roman_order = {
    {"M", 1000},
    {"CM", 900},
    {"D", 500},
    {"CD", 400},
    {"C", 100},
    {"XC", 90},
    {"L", 50},
    {"XL", 40},
    {"X", 10},
    {"IX", 9},
    {"V", 5},
    {"IV", 4},
    {"I", 1}
};

// Convert roman numeral string to integer, returns -1 if invalid
int roman_to_int(const string& s) {
    int n = s.size();
    int i = 0;
    int value = 0;
    while (i < n) {
        bool matched = false;
        for (auto& p : roman_order) {
            const string& sym = p.first;
            int val = p.second;
            int len = sym.size();
            if (i + len <= n && s.substr(i, len) == sym) {
                value += val;
                i += len;
                matched = true;
                break;
            }
        }
        if (!matched) return -1; // Invalid symbol
    }
    return value;
}

// Convert integer to roman numeral string (guaranteed canonical)
string int_to_roman(int x) {
    string res;
    for (auto& p : roman_order) {
        while (x >= p.second) {
            res += p.first;
            x -= p.second;
        }
    }
    return res;
}

// Checks if s is a valid canonical roman numeral for value val
bool is_canonical_roman(const string& s, int val) {
    return int_to_roman(val) == s;
}

// Checks if s is a valid roman numeral in canonical form
bool is_valid_roman(const string& s) {
    int val = roman_to_int(s);
    if (val == -1) return false;
    if (val < 1 || val > 3999) return false;
    return is_canonical_roman(s, val);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        string token = inf.readToken("[^ \n\r\t]+", "input_token");
        inf.readEoln();

        // Check if token is all digits (arabic number)
        bool is_digit = true;
        for (char c : token) {
            if (c < '0' || c > '9') {
                is_digit = false;
                break;
            }
        }

        if (is_digit) {
            // Check for leading zeros
            ensuref(token.size() == 1 || token[0] != '0', "Arabic number has leading zeros at test case %d: '%s'", tc+1, token.c_str());
            // Parse value
            long long val = 0;
            for (char c : token) {
                val = val * 10 + (c - '0');
                ensuref(val <= 3999, "Arabic number exceeds 3999 at test case %d: '%s'", tc+1, token.c_str());
            }
            ensuref(val >= 1 && val <= 3999, "Arabic number out of range at test case %d: '%s'", tc+1, token.c_str());
        } else {
            // Should be a roman numeral, only uppercase letters allowed
            for (char c : token) {
                ensuref(roman_single.count(c), "Invalid character '%c' in roman numeral at test case %d: '%s'", c, tc+1, token.c_str());
            }
            // Check canonical roman numeral in [1,3999]
            ensuref(is_valid_roman(token), "Invalid or non-canonical roman numeral at test case %d: '%s'", tc+1, token.c_str());
        }
    }

    inf.readEof();
}
