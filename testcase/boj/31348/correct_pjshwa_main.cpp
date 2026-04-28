#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
ll T[MAXV + 1], lp[MAXV + 1];
vector<int> pr;

void solve() {
  ll N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x, ox; cin >> x;
    ox = x;

    map<int, int> f;
    while (x > 1) {
      int p = lp[x];
      while (x % p == 0) x /= p, f[p] ^= 1;
    }

    ll b = 1;
    for (auto& [p, t] : f) if (t) b *= p;

    ll q = sqrt(ox * b);
    assert(q * q == ox * b);
    for (int m = 1;; ++m) {
      ll i = b * m * m;
      if (i > MAXV) break;

      ll j = q * m;
      if (j > MAXV) continue;

      if (i == j) ans += T[i] * (T[i] - 1) / 2;
      else ans += T[i] * T[j];
    }

    ++T[ox];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
