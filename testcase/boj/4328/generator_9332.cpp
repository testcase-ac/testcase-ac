#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string genCanonicalNonZero(int b, int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    if (len < 1) len = 1;
    string s;
    s.reserve(len);
    // First digit must be non-zero
    s.push_back(char('0' + rnd.next(1, b - 1)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(0, b - 1)));
    }
    return s;
}

long long parseToLL(const string &s, int b) {
    long long val = 0;
    for (char c : s) {
        int d = c - '0';
        val = val * b + d;
    }
    return val;
}

string toBase(long long x, int b) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        int d = int(x % b);
        s.push_back(char('0' + d));
        x /= b;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 5);

    vector<int> bases;
    vector<string> ps, ms;

    // Test 1: base 2 or 3, long p, small m (both non-zero)
    {
        int b = rnd.next(0, 1) ? 2 : 3;
        string p = genCanonicalNonZero(b, 30, 50);
        string m = genCanonicalNonZero(b, 2, 5);
        bases.push_back(b);
        ps.push_back(p);
        ms.push_back(m);
    }

    // Test 2: base 10, medium-long p, m with length close to 9 (both non-zero)
    {
        int b = 10;
        string p = genCanonicalNonZero(b, 25, 60);
        string m = genCanonicalNonZero(b, 7, 9);
        bases.push_back(b);
        ps.push_back(p);
        ms.push_back(m);
    }

    // Test 3: p < m (different base), both canonical non-zero
    {
        int b = rnd.next(2, 10);
        string m = genCanonicalNonZero(b, 2, 6);    // len >= 2
        int mLen = (int)m.size();
        // p has smaller length, so p < m
        string p = genCanonicalNonZero(b, 1, mLen - 1);
        bases.push_back(b);
        ps.push_back(p);
        ms.push_back(m);
    }

    // Test 4: p = 0, m non-zero
    {
        int b = rnd.next(2, 10);
        string p = "0";                             // canonical zero
        string m = genCanonicalNonZero(b, 1, 4);    // non-zero
        bases.push_back(b);
        ps.push_back(p);
        ms.push_back(m);
    }

    // Optional Test 5: one of several special patterns
    if (T == 5) {
        int type = rnd.next(0, 2); // 0: multiple-of-m, 1: m=1, 2: random moderate
        if (type == 0) {
            // p is a multiple of m (remainder 0)
            int b = rnd.next(2, 10);
            string m = genCanonicalNonZero(b, 1, 5);     // non-zero, len <= 5
            long long mVal = parseToLL(m, b);
            long long K = rnd.next(2, 20);               // small multiplier
            long long pVal = mVal * K;
            string p = toBase(pVal, b);                  // automatically canonical
            bases.push_back(b);
            ps.push_back(p);
            ms.push_back(m);
        } else if (type == 1) {
            // m = 1, so remainder is always 0
            int b = rnd.next(2, 10);
            string m = "1";                              // canonical non-zero
            string p = genCanonicalNonZero(b, 10, 50);   // arbitrary non-zero
            bases.push_back(b);
            ps.push_back(p);
            ms.push_back(m);
        } else {
            // Random moderate sizes, both non-zero
            int b = rnd.next(2, 10);
            string p = genCanonicalNonZero(b, 5, 40);
            string m = genCanonicalNonZero(b, 1, 8);
            bases.push_back(b);
            ps.push_back(p);
            ms.push_back(m);
        }
    }

    // Output all test cases
    for (int i = 0; i < (int)bases.size(); ++i) {
        println(bases[i], ps[i], ms[i]);
    }
    // Terminating line
    println(0);

    return 0;
}
