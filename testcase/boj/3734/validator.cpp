#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int BIG_BASE = 1000000000;
const int BIG_DIGITS = 9;

struct Big {
    vector<int> a;
    int sign = 1;

    Big(long long v = 0) { *this = v; }
    Big(const string& s) { read(s); }

    void operator=(long long v) {
        sign = 1;
        a.clear();
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        while (v > 0) {
            a.push_back(v % BIG_BASE);
            v /= BIG_BASE;
        }
    }

    bool isZero() const { return a.empty(); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }

    Big abs() const {
        Big r = *this;
        r.sign = 1;
        return r;
    }

    void read(const string& s) {
        sign = 1;
        a.clear();
        for (int i = (int)s.size() - 1; i >= 0; i -= BIG_DIGITS) {
            int x = 0;
            for (int j = max(0, i - BIG_DIGITS + 1); j <= i; ++j) {
                x = x * 10 + s[j] - '0';
            }
            a.push_back(x);
        }
        trim();
    }

    friend bool operator<(const Big& x, const Big& y) {
        if (x.sign != y.sign) return x.sign < y.sign;
        if (x.a.size() != y.a.size()) {
            return x.a.size() * x.sign < y.a.size() * y.sign;
        }
        for (int i = (int)x.a.size() - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) return x.a[i] * x.sign < y.a[i] * x.sign;
        }
        return false;
    }
    friend bool operator>(const Big& x, const Big& y) { return y < x; }
    friend bool operator<=(const Big& x, const Big& y) { return !(y < x); }
    friend bool operator>=(const Big& x, const Big& y) { return !(x < y); }
    friend bool operator==(const Big& x, const Big& y) { return !(x < y) && !(y < x); }
    friend bool operator!=(const Big& x, const Big& y) { return x < y || y < x; }

    Big operator-() const {
        Big r = *this;
        if (!r.isZero()) r.sign = -r.sign;
        return r;
    }

    Big operator+(const Big& v) const {
        if (sign == v.sign) {
            Big res = v;
            for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int)res.a.size()) res.a.push_back(0);
                res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
                carry = res.a[i] >= BIG_BASE;
                if (carry) res.a[i] -= BIG_BASE;
            }
            return res;
        }
        return *this - (-v);
    }

    Big operator-(const Big& v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                Big res = *this;
                for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry) res.a[i] += BIG_BASE;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }

    void operator+=(const Big& v) { *this = *this + v; }
    void operator-=(const Big& v) { *this = *this - v; }

    Big operator*(int v) const {
        Big res = *this;
        if (v < 0) {
            res.sign = -res.sign;
            v = -v;
        }
        long long carry = 0;
        for (int i = 0; i < (int)res.a.size() || carry; ++i) {
            if (i == (int)res.a.size()) res.a.push_back(0);
            long long cur = carry + 1LL * res.a[i] * v;
            res.a[i] = cur % BIG_BASE;
            carry = cur / BIG_BASE;
        }
        res.trim();
        return res;
    }

    Big operator*(const Big& v) const {
        Big res;
        res.sign = sign * v.sign;
        res.a.assign(a.size() + v.a.size(), 0);
        for (int i = 0; i < (int)a.size(); ++i) {
            long long carry = 0;
            for (int j = 0; j < (int)v.a.size() || carry; ++j) {
                long long cur = res.a[i + j] + carry;
                if (j < (int)v.a.size()) cur += 1LL * a[i] * v.a[j];
                res.a[i + j] = cur % BIG_BASE;
                carry = cur / BIG_BASE;
            }
        }
        res.trim();
        return res;
    }

    void operator*=(int v) { *this = *this * v; }

    Big operator/(int v) const {
        Big res = *this;
        if (v < 0) {
            res.sign = -res.sign;
            v = -v;
        }
        long long rem = 0;
        for (int i = (int)res.a.size() - 1; i >= 0; --i) {
            long long cur = res.a[i] + rem * BIG_BASE;
            res.a[i] = cur / v;
            rem = cur % v;
        }
        res.trim();
        return res;
    }

    int operator%(int v) const {
        if (v < 0) v = -v;
        long long m = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            m = (a[i] + m * BIG_BASE) % v;
        }
        return m * sign;
    }

    friend pair<Big, Big> divmod(const Big& a1, const Big& b1) {
        int norm = BIG_BASE / (b1.a.back() + 1);
        Big a = a1.abs() * norm;
        Big b = b1.abs() * norm;
        Big q, r;
        q.a.resize(a.a.size());

        for (int i = (int)a.a.size() - 1; i >= 0; --i) {
            r *= BIG_BASE;
            r += Big(a.a[i]);
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = (1LL * BIG_BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < Big(0)) {
                r += b;
                --d;
            }
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    Big operator/(const Big& v) const { return divmod(*this, v).first; }
    Big operator%(const Big& v) const { return divmod(*this, v).second; }
    void operator%=(const Big& v) { *this = *this % v; }
};

// Compare non-negative decimal strings without leading zeros (except "0").
// Return -1 if a<b, 0 if a==b, 1 if a>b.
int cmpDec(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

Big isqrt(Big n) {
    if (n <= Big(0)) return Big(0);

    Big lo = 1;
    Big hi("1000000000000000000000000000000000000000000000000000000000000");
    while (lo <= hi) {
        Big mid = (lo + hi) / 2;
        Big sq = mid * mid;
        if (sq <= n) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return hi;
}

Big modPow(Big base, Big exp, const Big& mod) {
    Big result = 1;
    base %= mod;
    while (exp > Big(0)) {
        if (exp % 2 != 0) result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

bool isProbablePrime(const Big& n) {
    if (n < Big(2)) return false;

    static const int smallPrimes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
        113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
        251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
        317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
        463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541
    };
    for (int p : smallPrimes) {
        if (n == Big(p)) return true;
        if (n % p == 0) return false;
    }

    Big d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d = d / 2;
        ++s;
    }

    for (int aInt : smallPrimes) {
        Big a = aInt;
        if (a >= n) continue;
        Big x = modPow(a, d, n);
        if (x == Big(1) || x == n - 1) continue;

        bool witness = true;
        for (int r = 1; r < s; ++r) {
            x = (x * x) % n;
            if (x == n - 1) {
                witness = false;
                break;
            }
        }
        if (witness) return false;
    }

    return true;
}

bool hasStatedFactorization(const Big& n, long long k) {
    Big root = isqrt(n / (int)k);
    Big low = root > Big(100005) ? root - 100005 : Big(2);
    Big high = root + 100005;

    for (Big p = low; p <= high; p += Big(1)) {
        if (n % p != Big(0)) continue;

        Big q = n / p;
        if (q < p) continue;

        Big diff = q - (p * (int)k);
        if (diff < Big(0)) diff = -diff;
        if (diff > Big(100000)) continue;

        return isProbablePrime(p) && isProbablePrime(q);
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n can be up to 10^120-1, so we read it as a string.
    // It is stated as a number, so we must enforce canonical form.
    string nStr = inf.readToken("[0-9]+", "n");
    inf.readSpace();

    // CHECK: Korean text says 1 < k, but the English statement and official
    // sample allow k = 1.
    long long k = inf.readLong(1LL, 100000000LL - 1LL, "k");
    inf.readEoln();
    (void)k;

    // Canonical form for n: no leading zeros (except single "0", but here n>1).
    ensuref(!(nStr.size() > 1 && nStr[0] == '0'),
            "n must not have leading zeros");

    // 1 < n < 10^120  => n > 1 and at most 120 digits (since 10^120 has 121 digits).
    ensuref(cmpDec(nStr, "1") > 0, "n must be > 1");
    ensuref(nStr.size() <= 120, "n must have at most 120 digits");

    Big n(nStr);
    ensuref(hasStatedFactorization(n, k),
            "n must equal p*q for primes p<=q with |q-k*p|<=100000");

    inf.readEof();
}
