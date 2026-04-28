#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MOD = 998244353;
ll fac[MAX + 1], ifac[MAX + 1];

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N); for (int& x : A) cin >> x;

  ll sum = accumulate(A.begin(), A.end(), 0), ans = 0;
  for (ll x : A) {
    sum -= x;

    ll cur = 0;
    for (int i = 0; i <= sum; i++) {
      ll acc = 0;
      for (ll j = 0; j <= i; j++) {
        ll add = (j * j) % MOD;
        add = (add * C(i, j)) % MOD;
        acc = (acc + add % MOD);
      }
      acc = (acc * fac[i]) % MOD;
      acc = (acc * fac[sum - i]) % MOD;
      cur = (cur + acc) % MOD;
    }
    cur = (cur * ifac[sum + x]) % MOD;
    ans = (ans + x * cur) % MOD;
  }

  cout << ans << '\n';
  // {
  //   queue<int> Q;
  //   for (int i = 0; i < N; i++) {
  //     int mS = A[i] - T + 1;
  //     while (!Q.empty() && Q.front() < mS) Q.pop();

  //     if (Q.size() < l) Q.push(A[i]), cout << A[i] << ' ';
  //     else if (Q.front() >= A[i]) { break; }
  //     else {
  //       int nS = Q.front() + 1; Q.pop();
  //       Q.push(nS + T - 1), cout << nS + T - 1 << ' ';
  //     }
  //   }
  // }
}

int main() {
  fast_io();

  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= MAX; i++) fac[i] = fac[i - 1] * i % MOD;
  ifac[MAX] = lpow(fac[MAX], MOD - 2, MOD);
  for (int i = MAX - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
