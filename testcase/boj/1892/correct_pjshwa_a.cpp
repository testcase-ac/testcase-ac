#include<bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

ll gcd(ll a, ll b) {
    if (!b) return a;
    else return gcd(b, a % b);
}

struct Fraction {
    ll numerator, denominator;
    Fraction(ll _n, ll _d) : numerator(_n), denominator(_d) {
        ll g = gcd(numerator, denominator);
        numerator /= g; denominator /= g;
    };
    Fraction() {};
    Fraction operator*(Fraction rhs) {
        ll num = numerator * rhs.numerator;
        ll den = denominator * rhs.denominator;
        ll g = gcd(num, den);
        num /= g; den /= g;
        return Fraction(num, den);
    }
    Fraction operator+(Fraction rhs) {
        ll num, den, g, lcm;
        if (denominator == rhs.denominator) {
            num = numerator + rhs.numerator;
            den = denominator;
        }
        else {
            g = gcd(denominator, rhs.denominator);
            lcm = (denominator / g) * (rhs.denominator / g);
            lcm *= g;
            num = numerator * (lcm / denominator) + rhs.numerator * (lcm / rhs.denominator);
            den = lcm;
        }
        g = gcd(num, den);
        num /= g; den /= g;
        return Fraction(num, den);
    }
};
ll dp[555][555];
Fraction f[55];

ll comb(int n, int r) {
    ll& ret = dp[n][r];
    if (ret != 0) return ret;
    if (n == r || r == 0) return ret = 1;
    if (n <= 1) return ret = 1;
    return ret = comb(n - 1, r - 1) + comb(n - 1, r);
}

int main() {
    ll N, K; cin >> N >> K;
    ll pw = 1;
    for (int i = 1; i <= K; ++i) pw *= 3ULL;
    ll pw2 = 1;
    Fraction ans(1, pw);
    for (ll i = K; i < 2 * K - 1; ++i) {
        f[i] = Fraction(comb(i - 1, K - 1) * pw2, pw);
        pw *= 3ULL; pw2 *= 2ULL;
    }
    for (ll i = 2 * K - 1; i <= N; ++i) {
        ll sum = 0;
        for (ll x = 0; x < K; ++x) {
            sum += comb(i - K, x);
        }
        f[i] = Fraction(comb(i - 1, K - 1) * sum, pw);
        pw *= 3ULL;
    }
    for (int i = K + 1; i <= N; ++i) ans = ans + f[i];
    cout << ans.numerator << ' ' << ans.denominator << '\n';
    return 0;
}
