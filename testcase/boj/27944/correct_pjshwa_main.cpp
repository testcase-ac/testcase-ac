#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<ll> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  ll ans = 1;
  for (ll e : {A[0], A[0] + 1}) {
    vector<ll> ps; ll oe = e;
    for (ll i = 2; i * i <= e; i++) {
      if (e % i == 0) ps.push_back(i);
      while (e % i == 0) e /= i;
    }
    if (e > 1) ps.push_back(e);

    for (ll p : ps) {
      bool able = true; ll g = oe;
      for (int i = 1; i < N; i++) {
        if (A[i] % p == 0) g = __gcd(g, A[i]);
        else if ((A[i] + 1) % p == 0) g = __gcd(g, (A[i] + 1));
        else able = false;
      }
      if (able) ans = max(ans, g);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
