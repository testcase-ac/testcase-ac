#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll G(ll v) {
  if (v % 2 == 0) return v / 2;
  return G((v - 1) / 2);
}

void solve() {
  ll N, ans = 0; cin >> N;
  for (int i = 1; i <= N; ++i) {
    ll x; cin >> x;
    ans ^= G(x);
  }
  cout << (ans ? "YES\n" : "NO\n");
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
