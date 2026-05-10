#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

// Compare two non-negative decimal integers in canonical string form
int cmpDecimal(const string &a, const string &b) {
    if (a.size() != b.size())
        return (a.size() < b.size()) ? -1 : 1;
    if (a == b) return 0;
    return (a < b) ? -1 : 1; // lexicographical; same length and digits only
}

// Subtract b from a (a > b >= 0), both in canonical decimal string form
string subDecimal(const string &a, const string &b) {
    string res(a.size(), '0');
    int carry = 0;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int k = (int)res.size() - 1;
    while (k >= 0) {
        int da = a[i] - '0';
        int db = (j >= 0 ? b[j] - '0' : 0);
        int cur = da - db - carry;
        if (cur < 0) {
            cur += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res[k] = char('0' + cur);
        --i; --j; --k;
    }
    // remove leading zeros
    size_t pos = res.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return res.substr(pos);
}

// Multiply non-negative long long a (<= 1e17) with big decimal string s (<=1e100)
// result fits in <= 1e117, i.e., at most 118 digits; always manageable as string
string mulLongLongDecimal(long long a, const string &s) {
    if (a == 0) return "0";
    if (s == "0") return "0";
    int n = (int)s.size();
    vector<int> res(n + 20, 0); // safe extra space
    long long carry = 0;
    int ri = (int)res.size() - 1;
    for (int i = n - 1; i >= 0; --i, --ri) {
        long long d = s[i] - '0';
        long long cur = d * a + carry;
        res[ri] = int(cur % 10);
        carry = cur / 10;
    }
    while (carry > 0 && ri >= 0) {
        res[ri] = int(carry % 10);
        carry /= 10;
        --ri;
    }
    string out;
    int start = 0;
    while (start < (int)res.size() && res[start] == 0) ++start;
    if (start == (int)res.size()) return "0";
    out.reserve(res.size() - start);
    for (int i = start; i < (int)res.size(); ++i)
        out.push_back(char('0' + res[i]));
    return out;
}

// Check that token is canonical positive decimal integer (no leading zeros, no sign)
void ensureCanonicalPositive(const string &s, const char *name) {
    ensuref(!s.empty(), "%s must be non-empty", name);
    for (char c : s)
        ensuref(c >= '0' && c <= '9', "%s must contain only digits 0-9", name);
    if (s.size() > 1)
        ensuref(s[0] != '0', "%s must not contain leading zeros", name);
    ensuref(s != "0", "%s must be > 0", name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Input format: three natural numbers a, b, c, each on its own line.
    // Limits:
    //   0 < c < b <= 10^100
    //   0 < a <= 10^17
    // Guarantee in statement: solution x is integer and natural (positive).

    string aStr = inf.readToken("[0-9]+", "a");
    inf.readEoln();
    string bStr = inf.readToken("[0-9]+", "b");
    inf.readEoln();
    string cStr = inf.readToken("[0-9]+", "c");
    inf.readEoln();

    // Canonical positive integers
    ensureCanonicalPositive(aStr, "a");
    ensureCanonicalPositive(bStr, "b");
    ensureCanonicalPositive(cStr, "c");

    // Bounds:
    // a <= 1e17  (fits in signed long long safely)
    ensuref(aStr.size() <= 18, "a has too many digits");
    long long a = 0;
    for (char ch : aStr) {
        a = a * 10 + (ch - '0');
    }
    ensuref(a >= 1 && a <= 100000000000000000LL,
            "a out of range: %lld, expected 1..1e17", a);

    // b, c <= 1e100 (length <= 101 digits since 10^100 is '1' followed by 100 zeros)
    ensuref(bStr.size() <= 101, "b has more than 101 digits");
    ensuref(cStr.size() <= 101, "c has more than 101 digits");

    // b <= 10^100
    {
        string lim = "1";
        lim.append(100, '0'); // 10^100
        ensuref(cmpDecimal(bStr, lim) <= 0,
                "b must be <= 10^100");
        ensuref(cmpDecimal(cStr, lim) <= 0,
                "c must be <= 10^100");
    }

    // 0 < c < b
    ensuref(cmpDecimal(cStr, bStr) < 0,
            "c must satisfy 0 < c < b");

    // From statement: solution x is integer and natural.
    // That means a divides (b - c) and (b - c) > 0.
    // We must verify it by actual computation (big integers).

    string diff = subDecimal(bStr, cStr); // b - c > 0 because c < b checked
    ensuref(diff != "0", "b - c must be > 0");

    // Check divisibility: a * x = diff for some integer x.
    // Compute x = floor(diff / a) using long division with small divisor a,
    // then verify that a * x == diff exactly.

    // Long division of big integer diff by small integer a
    string q;
    q.reserve(diff.size());
    long long rem = 0;
    for (char ch : diff) {
        rem = rem * 10 + (ch - '0');
        long long digit = rem / a;
        rem %= a;
        q.push_back(char('0' + (int)digit));
    }
    // canonicalize quotient (remove leading zeros)
    size_t pos = q.find_first_not_of('0');
    if (pos == string::npos) q = "0";
    else q = q.substr(pos);

    // Ensure exact divisibility
    ensuref(rem == 0, "a does not divide (b - c), but statement says solution x is integer");

    // Also, x must be natural number (>0)
    ensuref(q != "0", "x = (b - c) / a must be > 0 (natural)");

    // Extra safety: verify that a * x == diff
    string prod = mulLongLongDecimal(a, q);
    ensuref(prod == diff, "a * x != b - c due to arithmetic inconsistency");

    inf.readEof();
}
