#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

// Compare two non-negative decimal integer strings without leading zeros (except "0")
int cmpStrNum(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1; // lexicographical, since same length
}

// Multiply two non-negative integer strings (no leading zeros unless "0")
string mulStrNum(const string &a, const string &b) {
    int n = (int)a.size();
    int m = (int)b.size();
    vector<int> prod(n + m, 0);

    for (int i = n - 1; i >= 0; --i) {
        int da = a[i] - '0';
        int carry = 0;
        for (int j = m - 1; j >= 0; --j) {
            int db = b[j] - '0';
            int idx = (n - 1 - i) + (m - 1 - j);
            int &cell = prod[idx];
            long long cur = (long long)cell + (long long)da * db + carry;
            cell = (int)(cur % 10);
            carry = (int)(cur / 10);
        }
        int idx = (n - 1 - i) + m;
        while (carry > 0) {
            long long cur = (long long)prod[idx] + carry;
            prod[idx] = (int)(cur % 10);
            carry = (int)(cur / 10);
            ++idx;
        }
    }

    int k = (int)prod.size() - 1;
    while (k > 0 && prod[k] == 0) --k;
    string res;
    res.reserve(k + 1);
    for (; k >= 0; --k) res.push_back(char('0' + prod[k]));
    return res;
}

// Integer square root (floor) for big integer string n (non-negative, no leading zeros except "0")
string isqrtStr(const string &n) {
    if (n == "0" || n == "1") return n;

    int len = (int)n.size();
    int rootLen = (len + 1) / 2; // number of digits of sqrt

    // low = 10^(rootLen-1), high = 10^rootLen - 1
    string low = "1";
    for (int i = 1; i < rootLen; ++i) low.push_back('0');

    string high(rootLen, '9');

    auto incStr = [](string s) {
        int i = (int)s.size() - 1;
        int carry = 1;
        while (i >= 0 && carry) {
            int d = s[i] - '0' + carry;
            s[i] = char('0' + (d % 10));
            carry = d / 10;
            --i;
        }
        if (carry) s.insert(s.begin(), char('0' + carry));
        return s;
    };

    string ans = "0";
    while (cmpStrNum(low, high) <= 0) {
        // mid = (low + high) / 2 (string addition and division by 2)
        // We'll compute as numbers digit-wise.

        // addStr
        string a = low, b = high;
        if (a.size() < b.size()) a.insert(a.begin(), b.size() - a.size(), '0');
        if (b.size() < a.size()) b.insert(b.begin(), a.size() - b.size(), '0');
        int carry = 0;
        string sum(a.size(), '0');
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            int d = (a[i] - '0') + (b[i] - '0') + carry;
            sum[i] = char('0' + (d % 10));
            carry = d / 10;
        }
        if (carry) sum.insert(sum.begin(), char('0' + carry));

        // div2
        string mid;
        mid.reserve(sum.size());
        int rem = 0;
        for (char c : sum) {
            int d = rem * 10 + (c - '0');
            int q = d / 2;
            rem = d % 2;
            if (!mid.empty() || q != 0) mid.push_back(char('0' + q));
        }
        if (mid.empty()) mid = "0";

        string sq = mulStrNum(mid, mid);
        int c = cmpStrNum(sq, n);
        if (c <= 0) {
            ans = mid;
            low = incStr(mid);
        } else {
            // high = mid - 1
            string h = mid;
            int i = (int)h.size() - 1;
            int borrow = 1;
            while (i >= 0 && borrow) {
                int d = (h[i] - '0') - borrow;
                if (d < 0) {
                    d += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                h[i] = char('0' + d);
                --i;
            }
            // remove leading zeros
            int p = 0;
            while (p + 1 < (int)h.size() && h[p] == '0') ++p;
            high = h.substr(p);
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: positive integer, length <= 800, sqrt(N) is an integer.
    string N = inf.readToken("[0-9]{1,800}", "N");
    inf.readEoln();

    // Canonical form: no leading zeros, positive
    ensuref(N.size() == 1 || N[0] != '0',
            "N must not have leading zeros, got \"%s\"", N.c_str());
    ensuref(N != "0",
            "N must be positive, got 0");

    // Check that sqrt(N) is an integer by computing integer sqrt
    string r = isqrtStr(N);
    string sq = mulStrNum(r, r);
    ensuref(cmpStrNum(sq, N) == 0,
            "N must be a perfect square, but sqrt(%s)^2 = %s != %s",
            N.c_str(), sq.c_str(), N.c_str());

    inf.readEof();
}
