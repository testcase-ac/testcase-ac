#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<ll> PP{2, 3, 5, 7, 11};

ll lmult(ll a, ll b, ll mod) {
  ll M = (1 << 20) - 1;
  ll a1 = (M&a);
  ll a2 = ((a >> 20) & M);
  ll ret = a2 * b;
  ret %= mod;
  ret <<= 20;
  ret += a1 * b;
  ret %= mod;
  return ret;
}

ll lpow(ll base, ll exp, ll mod) {
  if (exp == 0) return 1;
  if (exp == 1) return base % mod;
  ll tmp = lpow(base, exp >> 1, mod);
  tmp = lmult(tmp, tmp, mod);
  if (exp & 1) tmp = lmult(tmp, base, mod);
  return tmp;
}

inline bool miller_rabin(ll n, ll a) {
  ll d = n - 1;
  while (d % 2 == 0) {
    if (lpow(a, d, n) == n - 1) return true;
    d /= 2;
  }
  ll r = lpow(a, d, n);
  return r == n - 1 || r == 1;
}

bool is_prime(ll n) {
  if (n == 1) return false;
  for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (!miller_rabin(n, a)) return false;
  }
  return true;
}

void solve() {
  for (int i = 1; i < 1e5; i++) {
    for (int m = 0; m < 10; m++) {
      string s = to_string(i);
      string r = s;
      reverse(r.begin(), r.end());

      s += to_string(m);
      s += r;

      ll u = stoll(s);
      if (is_prime(u)) PP.push_back(u);
    }
  }

  ll L, U;
  cin >> L >> U;

  // inclusive count
  cout << upper_bound(PP.begin(), PP.end(), U) - lower_bound(PP.begin(), PP.end(), L) << endl;  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
