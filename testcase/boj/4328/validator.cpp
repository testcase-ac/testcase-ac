#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// compare big non-negative integers in base 10 represented as strings without leading zeros (except "0")
int cmpStrNum(const string &a, const string &b) {
    if (a.size() != b.size()) return (a.size() < b.size()) ? -1 : 1;
    if (a == b) return 0;
    return (a < b) ? -1 : 1;
}

// divide big number given as decimal string by int d (1 <= d <= 10^9), return quotient string and remainder
pair<string,long long> divStrNumInt(const string &s, long long d) {
    string q;
    q.reserve(s.size());
    long long cur = 0;
    for (char c : s) {
        cur = cur * 10 + (c - '0');
        long long digit = cur / d;
        cur %= d;
        if (!q.empty() || digit != 0)
            q.push_back(char('0' + digit));
    }
    if (q.empty()) q = "0";
    return {q, cur};
}

// check canonical decimal non-negative integer string (no leading zeros unless "0")
bool isCanonicalNonNeg(const string &s) {
    if (s.empty()) return false;
    if (s.size() == 1) return s[0] >= '0' && s[0] <= '9';
    if (s[0] == '0') return false;
    for (char c : s) if (c < '0' || c > '9') return false;
    return true;
}

// check that token is base-b integer string (digits 0..b-1), length <= maxLen, canonical in that base
bool isCanonicalBaseB(const string &s, int b, int maxLen) {
    if ((int)s.size() == 0 || (int)s.size() > maxLen) return false;
    for (char c : s) if (c < '0' || c > '9') return false;
    for (char c : s) if (c - '0' >= b) return false;
    if (s.size() == 1) return true; // single digit always fine (including "0")
    if (s[0] == '0') return false;  // no leading zero for multi-digit
    return true;
}

// compute p mod m in base 10 big integers, with 0 <= p, 1 <= m, assume canonical decimal strings
long long modStrBig(const string &p, long long m) {
    long long r = 0;
    for (char c : p) {
        r = (r * 10 + (c - '0')) % m;
    }
    return r;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    int t = 0;

    while (true) {
        // First token of line: either single "0" ending input, or base b in [2,10] (canonical int)
        string first = inf.readToken("[0-9]+", "b_or_zero");
        if (first == "0") {
            // Must be exactly one token in this line
            inf.readEoln();
            break;
        }

        // validate first as canonical base-10 integer in [2,10]
        ensuref(isCanonicalNonNeg(first), "b must be a canonical non-negative decimal integer, got '%s'", first.c_str());
        long long b_ll = 0;
        for (char c : first) b_ll = b_ll * 10 + (c - '0');
        ensuref(2 <= b_ll && b_ll <= 10, "b must be between 2 and 10, got %lld", b_ll);
        int b = (int)b_ll;

        inf.readSpace();
        string p = inf.readToken("[0-9]+", "p");
        inf.readSpace();
        string m = inf.readToken("[0-9]+", "m");
        inf.readEoln();

        ++t;
        ensuref(t <= MAX_T, "number of test cases exceeds %d", MAX_T);

        // Validate p and m as base-b numbers with constraints
        ensuref(isCanonicalBaseB(p, b, 1000), "p must be a canonical base-%d integer with length 1..1000, using digits 0..%d, got '%s'", b, b-1, p.c_str());
        ensuref(isCanonicalBaseB(m, b, 9), "m must be a canonical base-%d integer with length 1..9, using digits 0..%d, got '%s'", b, b-1, m.c_str());

        // Convert m (base b) to decimal string and then to long long, ensure m > 0 and fits within reasonable bound
        // First convert base-b to decimal string by repeated algorithm, but since max length is 9 and b<=10, value fits in 32-bit.
        long long m_val = 0;
        for (char c : m) {
            m_val = m_val * b + (c - '0');
            ensuref(m_val <= (long long)1e9, "m is too large in decimal representation");
        }
        ensuref(m_val > 0, "m must be greater than 0");

        // Additionally, check that remainder exists and is < m is guaranteed by mathematics;
        // but ensure that computing p mod m in base b as documented doesn't overflow intermediates.
        // We can simulate modulo computation in base b with 64-bit.
        long long rem = 0;
        for (char c : p) {
            rem = (rem * b + (c - '0')) % m_val;
        }
        (void)rem; // silence unused warning
    }

    inf.readEof();
}
